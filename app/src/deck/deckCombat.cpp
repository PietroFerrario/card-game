#include "deckCombat.h"
#include "deckPlayer.h"
#include "deckEntry.h"
#include "cards/cardInstance.h"
#include "factories/ICardFactory.h"

DeckCombat::DeckCombat(const DeckPlayer &deck_player, const ICardFactory &factory) : m_factory{factory}
{
    // call factory here
}

void DeckCombat::populateDeck(const std::vector<DeckEntry> &cardList)
{
    for (const auto &deckEntry : cardList)
    {
        for (int i{0}; i < deckEntry.cardCount; ++i)
        {
            m_cards.emplace_back(m_factory.makeSingleCard(deckEntry.cardId));
        }
    }
}