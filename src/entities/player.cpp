#include "player.h"

#include <algorithm>

Player::Player(const std::vector<DeckEntry>& startingCardList, int hp)
    : Entity{hp}, m_deckPlayer{startingCardList}
{
}

void Player::increaseMoney(int amount)
{
    if (amount > 0)
    {
        m_money += amount;
    }
};

void Player::decreaseMoney(int amount)
{
    if (amount > 0)
    {
        m_money = std::max(0, m_money - amount);
    }
};

void Player::increasePopulation(int amount)
{
    if (amount > 0)
    {
        m_peopleInTheCaravan += amount;
    }
};

void Player::decreasePopulation(int amount)
{
    if (amount > 0)
    {
        m_peopleInTheCaravan = std::max(0, m_peopleInTheCaravan - amount);
    }
};
