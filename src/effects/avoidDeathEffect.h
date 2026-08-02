#ifndef AVOIDDEATHEFFECT_H
#define AVOIDDEATHEFFECT_H
#include "effect.h"

class AvoidDeathEffect : public Effect
{
  public:
    AvoidDeathEffect() = default;

    void resolve(CombatContext& combatContext, const CardParams& values) override;

  private:
};

#endif // AVOIDDEATHEFFECT_H
