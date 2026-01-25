#ifndef ENEMY_H
#define ENEMY_H

#include "enemyMove.h"
#include "entities/entity.h"

#include <vector>

class Enemy : public Entity
{
  public:
    Enemy(int hp) : Entity{hp} {}

  private:
    std::vector<EnemyMove> m_moves;
    int m_moveIndex;
};

#endif // ENEMY_H