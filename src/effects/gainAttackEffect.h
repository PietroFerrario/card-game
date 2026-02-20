#ifndef GAINATTACKEFFECT_H
#define GAINATTACKEFFECT_H

#include "combat/combatTarget.h"
#include "effect.h"

/**
 * @brief Effect that grants attack to a combat target.
 *
 * GainAttackEffect reads the armor value from EffectParams and grants it to either
 * the actor or the opponent, depending on the configured Target.
 *
 * The effect does not modify entity state directly; it requests the operation through
 * CombatContext.
 */
class GainAttackEffect : public Effect
{
  public:
    /**
     * @brief Constructs the effect with a fixed logical target.
     *
     * @param target Logical target selector (Self or Opponent).
     */
    GainAttackEffect(Target target) : m_target{target} {}

    /**
     * @brief Grants attack using EffectParams::attack.
     *
     * @param combatContext Current combat execution context.
     * @param values Numeric parameters used during resolution.
     */
    void resolve(CombatContext& combatContext, const EffectParams& values) override;

  private:
    Target m_target;
};

#endif // GAINATTACKEFFECT_H