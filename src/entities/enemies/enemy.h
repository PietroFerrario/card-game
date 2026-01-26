#ifndef ENEMY_H
#define ENEMY_H

#include "enemyMove.h"
#include "entities/entity.h"

#include <vector>

class Enemy : public Entity
{
  public:
    Enemy(int hp);
    const EnemyMove& nextMove();

  protected:
    std::vector<EnemyMove> m_moves{};
    int m_moveIndex{0};

    void advanceMoves();
};

#endif // ENEMY_H