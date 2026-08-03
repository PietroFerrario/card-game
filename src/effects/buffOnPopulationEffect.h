#ifndef BUFFONPOPULATIONEFFECT_H
#define BUFFONPOPULATIONEFFECT_H

#include "combat/combatTarget.h"
#include "effect.h"

class BuffOnPopulationEffect : public Effect
{
  public:
    BuffOnPopulationEffect(Target target) : m_target{target} {}

    void resolve(CombatContext& combatContext, const CardParams& values) override;

  private:
    Target m_target;
};

#endif // BUFFONPOPULATIONEFFECT_H
