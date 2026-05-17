#include "player.h"

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
        m_money = std::min(0, m_money - amount);
    }
};