#include "cardMatch.h"
#include "cards/CardInstance.h"
#include "cards/cardDefinition.h"
#include "cassert"
#include "combat/combatContext.h"
#include "combat/combatEvents.h"
#include "combat/combatTarget.h"
#include "effects/effect.h"
#include "entities/enemies/enemy.h"
#include "entities/enemies/enemyMove.h"
#include "entities/player.h"
#include "util/debug.h"

CardMatch::CardMatch(GameConfig& cardConfig, IMatchView& matchView, const ICardFactory& cardFactory,
                     Player& player, Enemy& enemy)
    : m_gameConfig{cardConfig}, m_matchView{matchView}, m_cardFactory{cardFactory},
      m_player{player}, m_enemy{enemy}, m_deckCombat{m_player.getDeckPlayer(), m_cardFactory}
{
}

// legacy: To be removed
void CardMatch::gainArmor(int defense) { m_player.increaseArmor(defense); }

void CardMatch::drawMultipleCardsNoEffect(int amount)
{

    DrawData drawData{m_deckCombat.drawMultipleCards(amount)};

    DEBUG_LOG("Drawing cards completed.");
    m_matchView.showDrawCards(drawData);
}

void CardMatch::playCard(int handIndex, CombatContext& currentContext)
{

    std::unique_ptr<CardInstance> cardBeingPlayed = m_deckCombat.takeFromHand(handIndex);
    if (!cardBeingPlayed)
    {
        return;
    }
    DEBUG_LOG("Playing card: " << cardBeingPlayed->getCardDefinition().getID()
                               << " from hand index: " << handIndex);

    std::vector<std::string> effectMessage;

    CombatContext::EffectMessageScope logScope(currentContext, effectMessage);

    // Possible to implement an extraction of CardParams at the beginning. Then pass it to
    // .resolve -> Less call to getEffectParams. Not necessary for now, possible future
    // implementation.
    for (const auto& effectPtr : cardBeingPlayed->getCardDefinition().getEffectList())
    {
        effectPtr->resolve(currentContext, cardBeingPlayed->getCardParams());
    }
    DEBUG_LOG("Applied all the effect from card " << cardBeingPlayed->getCardDefinition().getID()
                                                  << ".");

    m_matchView.showPlayedCardName(cardBeingPlayed->getCardDefinition().getName());

    if (!effectMessage.empty())
    {
        m_matchView.showEffectMessage(effectMessage);
    }

    if (auto drawData{currentContext.getDrawData()})
    {
        m_matchView.showDrawCards(drawData.value());
    }

    m_deckCombat.discard(std::move(cardBeingPlayed));
}

void CardMatch::spendAction(TurnData& turnData)
{
    assert(turnData.playerRemainingActions > 0 && "Trying to spend an action with 0 remaining");
    --turnData.playerRemainingActions;
}

void CardMatch::reduceAction(TurnData& turnData, int amount)
{
    if (amount <= 0)
        return;

    turnData.playerRemainingActions = std::max(0, turnData.playerRemainingActions - amount);
}

bool CardMatch::updateMatchState()
{
    bool playerDead = m_combatSystem.isDead(m_player);
    bool enemyDead = m_combatSystem.isDead(m_enemy);

    if (playerDead && !enemyDead)
    {
        m_matchData.matchState = MatchState::EnemyWon;
        return true;
    }
    else if (enemyDead && !playerDead)
    {
        m_matchData.matchState = MatchState::PlayerWon;
        return true;
    }
    else if (enemyDead && playerDead)
    {
        m_matchData.matchState = MatchState::MutualDestruction;
        return true;
    }
    return false;
}

// Implement returning the MatchState -> In order for the main to manage it
MatchData CardMatch::turnLoop()
{
    m_matchView.showStartOfMatch(m_enemy.getName());

    DEBUG_LOG("Starting turn loop");
    while (m_matchData.matchState == MatchState::Running)
    {
        DEBUG_LOG("Match state: Running. Turn continues");
        TurnData turnData{m_gameConfig.actionsPerTurn, m_gameConfig.cardsDrawnPerTurn};
        playerTurnSetup(turnData);
        enemyTurn(turnData);
        playerTurn(turnData);
        damagePhase();
        if (updateMatchState())
        {
            // Refactor Match result to be shown in the Event Sequence, not in the CardMatch!
            m_matchView.showEndOfMatch(m_matchData);
            resetPhase();
            return m_matchData;
        }
        resetPhase();
    }
    return m_matchData;
}

bool CardMatch::canPlayerAct(TurnData& currentTurnData)
{
    DEBUG_LOG("Checking is the player can act in this turn");

    const bool hasAction = currentTurnData.playerRemainingActions > 0;
    const bool hasCards = m_deckCombat.getHandSize() > 0;

    const bool isUnderCardsLimit =
        !currentTurnData.cardsToPlayLimit.has_value() ||
        currentTurnData.cardsPlayed < currentTurnData.cardsToPlayLimit.value();

    return hasAction && hasCards && isUnderCardsLimit;
}

void CardMatch::playerTurnSetup(const TurnData& currentTurnData)
{
    m_matchView.showPlayerTurnStart(m_matchData);
    drawMultipleCardsNoEffect(currentTurnData.initialCardsToDraw);
}

void CardMatch::playerTurn(TurnData& currentTurnData)
{
    DEBUG_LOG("Starting player turn: Drawing" << m_gameConfig.cardsDrawnPerTurn << " cards");

    CombatContext currentContext{m_combatSystem, m_player, m_enemy, m_deckCombat, currentTurnData};

    while (canPlayerAct(currentTurnData))
    {
        DEBUG_LOG("Player can act: Starting valid action loop");

        m_matchView.showRecurringMatchStatus(m_matchData, currentTurnData, m_player, m_enemy);
        m_matchView.showCurrentHand(m_deckCombat.getHandView());

        DEBUG_LOG("Asking the player how to act: Play a card or Pass");
        PlayCardDecision decision{
            m_matchView.askPlayerAction(static_cast<int>(m_deckCombat.getHandSize()))};

        if (decision.playerChoice == PlayerChoice::PlayCard)
        {
            playCard(decision.selectedCard.value(), currentContext);
            DEBUG_LOG("Spending one action");
            // Add validation to the spending of action only the the card was actually played.
            spendAction(currentTurnData);
            ++currentTurnData.cardsPlayed;
        }
        else if (decision.playerChoice == PlayerChoice::PassTurn)
        {
            DEBUG_LOG("Passing: no action spent");
            m_matchView.showPassingTurn();
            break;
        }

        DEBUG_LOG("Ending action loop");
    }
}

void CardMatch::enemyTurn(TurnData& currentTurnData)
{
    DEBUG_LOG("Starting enemy action");
    const EnemyMove& currentMove = m_enemy.nextMove();

    std::vector<std::string> effectMessage;

    CombatContext currentContext{m_combatSystem, m_enemy, m_player, m_deckCombat, currentTurnData};

    CombatContext::EffectMessageScope logScope(currentContext, effectMessage);

    for (const auto& effectPtr : currentMove.effectList)
    {
        effectPtr->resolve(currentContext, currentMove.effectParams);
    }
    DEBUG_LOG("Applied all the effect from " << currentMove.name << "");

    m_matchView.showEnemyMove(m_enemy.getName(), currentMove.name, currentMove.description);

    if (!effectMessage.empty())
    {
        m_matchView.showEffectMessage(effectMessage);
    }
}

void CardMatch::damagePhase()
{
    DamageResult enemyResult{m_combatSystem.dealDamage(m_player, m_enemy.getAttack())};
    m_matchView.showDamageResult(enemyResult);

    DamageResult playerResult{m_combatSystem.dealDamage(m_enemy, m_player.getAttack())};
    m_matchView.showDamageResult(playerResult);
}

void CardMatch::resetPhase()
{
    m_combatSystem.endTurnReset(m_player, m_enemy);
    m_deckCombat.movePlayedToDiscardEndTurn();
    m_deckCombat.discardHandEndTurn();
    m_matchView.showEndOfTurn(m_matchData);
    ++m_matchData.turnNumber;
}
