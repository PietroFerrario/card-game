#include "cardMatch.h"
#include "cards/CardInstance.h"
#include "cards/cardDefinition.h"
#include "cards/effect.h"
#include "entities/enemies/enemy.h"
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

    for (const auto& effectPtr : cardBeingPlayed->getCardDefinition().getEffectList())
    {
        effectPtr->apply(*this, *cardBeingPlayed);
    }
    DEBUG_LOG("Applied all the effect from card " << cardBeingPlayed->getCardDefinition().getID()
                                                  << ".");

    m_deckCombat.discard(std::move(cardBeingPlayed));
}