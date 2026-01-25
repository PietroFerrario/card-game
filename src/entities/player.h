#ifndef PLAYER_H
#define PLAYER_H

#include "deck/deckEntry.h"
#include "deck/deckPlayer.h"

#include "entity.h"

#include <string>
#include <string_view>
#include <vector>

class Player : public Entity
{
  public:
    Player() {}
    Player(const std::vector<DeckEntry>& startingCardList, int hp = 10);

    void setName(std::string_view name) { m_name = name; }
    std::string_view getName() const { return m_name; }

    const DeckPlayer& getDeckPlayer() { return m_deckPlayer; }

  private:
    DeckPlayer m_deckPlayer;
};

#endif