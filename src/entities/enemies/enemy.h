#ifndef ENEMY_H
#define ENEMY_H

#include "entities/entity.h"

class Enemy : public Entity
{
  public:
    Enemy(int hp, int attack);

  private:
    int m_attack{};
};

#endif // ENEMY_H