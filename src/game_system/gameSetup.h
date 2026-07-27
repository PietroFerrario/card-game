#ifndef GAMESETUP_H
#define GAMESETUP_H

#include "deck/deckPlayer.h"
#include "factories/ICardFactory.h"

namespace gameSetup
{
inline int calculateInitialPopulation(const DeckPlayer& deckPlayer, const ICardFactory& cardFactory)
{
    int initialPopulation{0};
    for (const auto& deckEntry : deckPlayer.getCardList())
    {
        initialPopulation += cardFactory.getCardPopulation(deckEntry.cardId);
    }

    return initialPopulation;
}
} // namespace gameSetup

#endif // GAMESETUP_H
