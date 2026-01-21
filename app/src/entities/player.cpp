#include "player.h"

Player::Player(const std::vector<DeckEntry>& startingCardList, int hp)
    : m_deckPlayer{startingCardList}, m_hp{hp}
{
}

void Player::takeDamage(int amount) { m_hp -= amount; }
void Player::heal(int amount) { m_hp += amount; }

void Player::increaseArmor(int amount) { m_armor += amount; }

void Player::lowerArmor(int amount)
{
    m_armor -= amount;
    if (m_armor <= 0)
        m_armor = 0;
}
