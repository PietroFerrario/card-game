#ifndef MAINTAINEXCESSARMOREFFECT_H
#define MAINTAINEXCESSARMOREFFECT_H

#include "combat/combatTarget.h"
#include "effect.h"

class MaintainExcessArmorEffect : public Effect
{
  public:
    MaintainExcessArmorEffect(Target target) : m_target{target} {}

    void resolve(CombatContext& combatContext, const CardParams& values) override;

  private:
    Target m_target;
};

#endif // MAINTAINEXCESSARMOREFFECT_H
