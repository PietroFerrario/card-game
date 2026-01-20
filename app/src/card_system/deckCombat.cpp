#include "deckCombat.h"
#include "deckPlayer.h"
#include "card.h"

DeckCombat::DeckCombat(const DeckPlayer &deck_player)
{
    // Implement CardFactory
}

void DeckCombat::populateDeck(const std::vector<DeckEntry> &cardList)
{
    for (auto &deckEntry : cardList)
    {
        for (int i{0}; i < deckEntry.cardCount; ++i)
        {

            m_cards.emplace_back(makeSingleCard(deckEntry.cardId));
        }
    }
}