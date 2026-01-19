#include "player.h"

void Player::takeDamage(int amount) { m_hp -= amount; }
void Player::heal(int amount) { m_hp += amount; }

void Player::increaseArmor(int amount) { m_armor += amount; }

void Player::lowerArmor(int amount)
{
    m_armor -= amount;
    if (m_armor <= 0)
        m_armor = 0;
}
