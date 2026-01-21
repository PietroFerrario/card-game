#include "enemy.h"

Enemy::Enemy(int hp, int attack) : m_hp{hp}, m_attack{attack} {}

void Enemy::takeDamage(int amount) { m_hp -= amount; }
void Enemy::heal(int amount) { m_hp += amount; }