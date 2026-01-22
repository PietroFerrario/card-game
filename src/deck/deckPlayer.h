#ifndef DECKPLAYER_H
#define DECKPLAYER_H

#include "deckEntry.h"

#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

class DeckPlayer
{
  public:
    DeckPlayer() {}
    DeckPlayer(std::vector<DeckEntry> startingCardList, int maxCardNumbers = 20);

    friend std::ostream& operator<<(std::ostream& out, const DeckPlayer& deck);

    int getCurrentCardNumber() const;
    bool isCardPresent(std::string_view cardId) const;

    bool addCard(std::string_view cardId);
    bool removeCard(std::string_view cardId);

    const std::vector<DeckEntry>& getCardList() const { return m_cardsList; }

  private:
    int m_maxCardNumber{};
    int m_minCardNumber{5};
    std::vector<DeckEntry> m_cardsList{};
};

#endif // DECKPLAYER_H