#ifndef MAINTAINEXCESSARMOREFFECT_H
#define MAINTAINEXCESSARMOREFFECT_H

#include "effect.h"

class MaintainExcessArmorEffect : public Effect
{
  public:
    MaintainExcessArmorEffect() = default;

    void resolve(CombatContext& combatContext, const CardParams& values) override;

  private:
};

#endif // MAINTAINEXCESSARMOREFFECT_H
