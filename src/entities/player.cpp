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
        m_population += amount;
    }
};

void Player::decreasePopulation(int amount)
{
    if (amount > 0)
    {
        m_population = std::max(0, m_population - amount);
    }
};

bool Player::addCardToDeck(std::string_view cardId, int population)
{
    if (!m_deckPlayer.addCard(cardId))
        return false;

    increasePopulation(population);
    return true;
}

void Player::multiplyAttack(double multiplier)
{
    if (multiplier > 0)
    {
        m_attack = static_cast<int>(m_attack * multiplier);
    }
}

void Player::multiplyArmor(double multiplier)
{
    if (multiplier > 0)
    {
        m_armor = static_cast<int>(m_armor * multiplier);
    }
}
