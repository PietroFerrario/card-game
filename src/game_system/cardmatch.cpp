#include "cardMatch.h"
#include "cards/CardInstance.h"
#include "cards/cardDefinition.h"
#include "combat/combatContext.h"
#include "effects/effect.h"
#include "entities/enemies/enemy.h"
#include "entities/enemies/enemyMove.h"
#include "entities/player.h"
#include "util/debug.h"

CardMatch::CardMatch(Player& player, Enemy& enemy)
    : m_player{player}, m_enemy{enemy}, m_cardFactory{},
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

    CombatContext currentContext{m_combatSystem, m_player, m_enemy};

    // Possible to implement an extraction of EffectParams at the beginning. Then pass it to
    // .resolve -> Less call to getEffectParams. Not necessary for now, possible future
    // implementation.
    for (const auto& effectPtr : cardBeingPlayed->getCardDefinition().getEffectList())
    {
        effectPtr->resolve(currentContext, cardBeingPlayed->getEffectParams());
    }
    DEBUG_LOG("Applied all the effect from card " << cardBeingPlayed->getCardDefinition().getID()
                                                  << ".");

    m_deckCombat.discard(std::move(cardBeingPlayed));
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