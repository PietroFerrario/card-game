#ifndef INCREASEDAMAGEENEMYMOVE_H
#define INCREASEDAMAGEENEMYMOVE_H

#include "effect.h"

class IncreaseDamageEnemyMove : public Effect
{
  public:
    IncreaseDamageEnemyMove() = default;

    void resolve(CombatContext& combatContext, const CardParams& values) override;

  private:
};

#endif // INCREASEDAMAGEENEMYMOVE_H
