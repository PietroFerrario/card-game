#include "cardmatch.h"
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
    DEBUG_LOG("Card amount in HandPile: " << m_deckCombat.getHandPile().size() << ".");
    if (m_deckCombat.getHandPile().size() <= 0)
    {
        DEBUG_LOG("The HandPile is empty, you can't play more cards.");
    }
    else if (m_deckCombat.getHandPile().size() > handIndex)
    {
        std::unique_ptr<CardInstance>& cardToPlay = m_deckCombat.getHandPile()[handIndex];
        DEBUG_LOG("Selected a valid card to play, at index: " << handIndex << ".");

        for (const auto& effectPtr : cardToPlay->getCardDefinition().getEffectList())
        {
            effectPtr->apply(*this, *cardToPlay);
        }
        DEBUG_LOG("Applied all the effect from card " << cardToPlay->getCardDefinition().getID()
                                                      << ".");

        m_deckCombat.discardFromHand(handIndex);
    }
    else
    {
        DEBUG_LOG("Index " << handIndex << " is not a valid one to play a card.");
    }
}