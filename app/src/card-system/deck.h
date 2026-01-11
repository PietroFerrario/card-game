#ifndef DECK_H
#define DECK_H

#include <vector>

#include "card.h"

class Deck
{
public:
    int getCurrentCardNumber() const;

private:
    int m_max_card_number{};
    std::vector<Card> m_cards{};
};

#endif // DECK_H