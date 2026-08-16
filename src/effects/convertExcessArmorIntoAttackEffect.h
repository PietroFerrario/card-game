#ifndef CONVERTEXCESSARMORINTOATTACKEFFECT_H
#define CONVERTEXCESSARMORINTOATTACKEFFECT_H

#include "combat/combatTarget.h"
#include "effect.h"

class ConvertExcessArmorIntoAttackEffect : public Effect
{

  public:
    ConvertExcessArmorIntoAttackEffect(Target target) : m_target{target} {}

    void resolve(CombatContext& combatContext, const CardParams& values) override;

  private:
    Target m_target;
};

#endif // CONVERTEXCESSARMORINTOATTACKEFFECT_H