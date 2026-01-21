#include "deckCombat.h"
#include "cards/cardDefinition.h"
#include "cards/cardInstance.h"
#include "deckEntry.h"
#include "deckPlayer.h"
#include "factories/ICardFactory.h"

#include "util/debug.h"

DeckCombat::DeckCombat(const DeckPlayer& deck_player, const ICardFactory& factory)
    : m_factory{factory}
{
    populateDeck(deck_player.getCardList());
}

void DeckCombat::populateDeck(const std::vector<DeckEntry>& cardList)
{
    for (const auto& deckEntry : cardList)
    {
        for (int i{0}; i < deckEntry.cardCount; ++i)
        {
            m_cards.emplace_back(m_factory.makeSingleCard(deckEntry.cardId));
        }
    }
}

void DeckCombat::drawCard()
{
    if (!m_cards.empty())
    {
        m_handPile.emplace_back(std::move(m_cards.back()));
        m_cards.pop_back();
        DEBUG_LOG("Drawn " << m_handPile.back()->getCardDefinition().getID()
                           << " from the deck, placed in the handPile.");
    }
    else
    {
        DEBUG_LOG("The deck is empty: no more cards to drawn");
    }
}