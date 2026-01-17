#ifndef DECKCOMBAT_H
#define DECKCOMBAT_H

#include "deckPlayer.h"
#include "card.h"

#include <vector>
#include <string>
#include <memory>

class DeckCombat
{
public:
    DeckCombat(const DeckPlayer &deck_player);

private:
    std::vector<std::unique_ptr<Card>> m_cards;
};

#endif // DECKCOMBAT_H
