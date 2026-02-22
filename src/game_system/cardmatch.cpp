#include "cardMatch.h"
#include "cards/CardInstance.h"
#include "cards/cardDefinition.h"
#include "cassert"
#include "combat/combatContext.h"
#include "combat/combatTarget.h"
#include "effects/effect.h"
#include "entities/enemies/enemy.h"
#include "entities/enemies/enemyMove.h"
#include "entities/player.h"
#include "util/debug.h"

CardMatch::CardMatch(IMatchView& matchView, Player& player, Enemy& enemy)
    : m_matchView{matchView}, m_player{player}, m_enemy{enemy}, m_cardFactory{},
      m_deckCombat{m_player.getDeckPlayer(), m_cardFactory}
{
}

void CardMatch::gainArmor(int defense) { m_player.increaseArmor(defense); }

void CardMatch::drawMultipleCards(int amount)
{
    DEBUG_LOG("Requesting to draw " << amount << " cards from the deck: ...");
    for (int i{0}; i < amount; i++)
    {
        m_deckCombat.drawCard();
    }
    DEBUG_LOG("Drawing cards completed.");
}

void CardMatch::playCard(int handIndex)
{

    std::unique_ptr<CardInstance> cardBeingPlayed = m_deckCombat.takeFromHand(handIndex);
    if (!cardBeingPlayed)
    {
        return;
    }
    DEBUG_LOG("Playing card: " << cardBeingPlayed->getCardDefinition().getID()
                               << " from hand index: " << handIndex);

    std::vector<std::string> effectMessage;

    CombatContext currentContext{m_combatSystem, m_player, m_enemy, &effectMessage};

    // Possible to implement an extraction of EffectParams at the beginning. Then pass it to
    // .resolve -> Less call to getEffectParams. Not necessary for now, possible future
    // implementation.
    for (const auto& effectPtr : cardBeingPlayed->getCardDefinition().getEffectList())
    {
        effectPtr->resolve(currentContext, cardBeingPlayed->getEffectParams());
    }
    DEBUG_LOG("Applied all the effect from card " << cardBeingPlayed->getCardDefinition().getID()
                                                  << ".");

    m_matchView.showPlayedCardName(cardBeingPlayed->getCardDefinition().getName());

    if (!effectMessage.empty())
    {
        m_matchView.showEffectMessage(effectMessage);
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

void CardMatch::turnLoop()
{
    DEBUG_LOG("Starting turn loop");
    while (m_matchData.matchState == MatchState::Running)
    {
        DEBUG_LOG("Match state: Running. Turn continues");
        TurnData turnData;
        playerTurn(turnData);
        enemyTurn();
        damagePhase();
        // resetPhase();
    }
}

bool CardMatch::canPlayerAct(TurnData& currentTurnData)
{
    DEBUG_LOG("Checking is the player can act in this turn");
    return currentTurnData.playerRemainingActions > 0 &&
           static_cast<int>(m_deckCombat.getHandSize());
}

void CardMatch::playerTurn(TurnData& currentTurnData)
{
    DEBUG_LOG("Starting player turn: Drawing 2 cards");
    drawMultipleCards(2);

    while (canPlayerAct(currentTurnData))
    {
        DEBUG_LOG("Player can act: Starting valid action loop");
        m_matchView.showRecurringMatchStatus(m_matchData, currentTurnData, m_player, m_enemy);
        m_matchView.showCurrentHand(m_deckCombat.getHandView());

        DEBUG_LOG("Asking which card to play (Inside playerTurn)");
        int cardToPlayIndex{
            m_matchView.askCardToPlay(static_cast<int>(m_deckCombat.getHandSize()))};
        playCard(cardToPlayIndex);

        DEBUG_LOG("Spending one action");
        spendAction(currentTurnData);
        ++currentTurnData.cardsPlayed;

        DEBUG_LOG("Ending action loop");
    }
}

void CardMatch::enemyTurn()
{
    DEBUG_LOG("Starting enemy action");
    const EnemyMove& currentMove = m_enemy.nextMove();

    CombatContext currentContext{m_combatSystem, m_enemy, m_player};

    for (const auto& effectPtr : currentMove.effectList)
    {
        effectPtr->resolve(currentContext, currentMove.effectParams);
    }
    DEBUG_LOG("Applied all the effect from " << currentMove.name << "");
}

void CardMatch::damagePhase()
{
    CombatContext playerDamageContext{m_combatSystem, m_player, m_enemy};
    Target playerTarget{Target::Opponent};
    DamageResult playerResult{playerDamageContext.dealDamage(playerTarget, m_player.getAttack())};
    m_matchView.showDamageResult(playerResult);

    CombatContext enemyDamageContext{m_combatSystem, m_enemy, m_player};
    Target enemyTarget{Target::Opponent};
    DamageResult enemyResult{enemyDamageContext.dealDamage(enemyTarget, m_enemy.getAttack())};
    m_matchView.showDamageResult(enemyResult);
}
