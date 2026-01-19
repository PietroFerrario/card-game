#ifndef DECKPLAYER_H
#define DECKPLAYER_H

#include "deckEntry.h"

#include <vector>
#include <memory>
#include <string>
#include <string_view>
#include <iostream>
#include <utility>

class DeckPlayer
{
public:
    DeckPlayer(std::vector<DeckEntry> &starting_card_list, int max_card_number = 20);

    friend std::ostream &operator<<(std::ostream &out, const DeckPlayer &deck);

    const int getCurrentCardNumber() const;
    bool isCardPresent(std::string_view card_id) const;

    bool addCard(std::string_view card_id);
    bool removeCard(std::string_view card_id);

private:
    int m_max_card_number{};
    int m_min_card_number{5};
    std::vector<DeckEntry> m_cards_list{};
};

#endif // DECKPLAYER_H