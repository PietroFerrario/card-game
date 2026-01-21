#include "cardmatch.h"
#include "entities/enemies/enemy.h"
#include "entities/player.h"

CardMatch::CardMatch(Player& player, Enemy& enemy) : m_player{player}, m_enemy{enemy} {}

void CardMatch::gainArmor(int defense) { m_player.increaseArmor(defense); }