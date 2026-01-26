#ifndef ENEMY_H
#define ENEMY_H

#include "enemyMove.h"
#include "entities/entity.h"

#include <vector>

class Enemy : public Entity
{
  public:
    const EnemyMove& nextMove();

  protected:
    Enemy(int hp);
    std::vector<EnemyMove> m_moves{};
    int m_moveIndex{0};
};

#endif // ENEMY_H