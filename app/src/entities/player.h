#ifndef PLAYER_H
#define PLAYER_H

#include "deck/deckEntry.h"
#include "deck/deckPlayer.h"

#include <string>
#include <string_view>
#include <vector>

class Player
{
  public:
    Player(const std::vector<DeckEntry>& startingCardList, int hp = 10);

    void setName(std::string_view name) { m_name = name; }
    std::string_view getName() const { return m_name; }

    int getHp() const { return m_hp; }

    int getArmor() const { return m_armor; }
    void resetArmor() { m_armor = 0; }
    void lowerArmor(int amount);
    void increaseArmor(int amount);

    void takeDamage(int amount);
    void heal(int amount);

    const DeckPlayer& getDeckPlayer() { return m_deckPlayer; }

  private:
    int m_hp{};
    int m_armor{};
    std::string m_name{};

    DeckPlayer m_deckPlayer;
};

#endif