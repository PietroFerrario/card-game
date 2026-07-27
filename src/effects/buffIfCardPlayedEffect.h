#ifndef BUFFIFCARDPLAYEDEFFECT_H
#define BUFFIFCARDPLAYEDEFFECT_H

#include "combat/combatTarget.h"
#include "effect.h"

class BuffIfCardPlayedEffect : public Effect
{
  public:
    BuffIfCardPlayedEffect(Target target) : m_target{target} {}

    void resolve(CombatContext& combatContext, const CardParams& values) override;

  private:
    Target m_target;
};

#endif // BUFFIFCARDPLAYEDEFFECT_H
