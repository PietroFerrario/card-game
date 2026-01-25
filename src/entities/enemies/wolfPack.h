#ifndef WOLFPACK_H
#define WOLFPACK_H

#include "enemy.h"

class WolfPack : public Enemy
{
  public:
    WolfPack(int hp = 30);

    void packTactics();

  private:
};
#endif // WOLFPACK_H