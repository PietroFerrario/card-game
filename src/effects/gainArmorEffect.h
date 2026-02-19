#ifndef GAINBLOCKEFFECT_H
#define GAINBLOCKEFFECT_H

#include "combat/combatTarget.h"
#include "effect.h"

/**
 * @brief Effect that grants armor to a combat target.
 *
 * GainArmorEffect reads the armor value from EffectParams and grants it to either
 * the actor or the opponent, depending on the configured Target.
 *
 * The effect does not modify entity state directly; it requests the operation through
 * CombatContext.
 */
class GainArmorEffect : public Effect
{
  public:
    /**
     * @brief Constructs the effect with a fixed logical target.
     *
     * @param target Logical target selector (Self or Opponent).
     */
    GainArmorEffect(Target target) : m_target{target} {}

    /**
     * @brief Grants armor using EffectParams::armor.
     *
     * @param combatContext Current combat execution context.
     * @param values Numeric parameters used during resolution.
     */
    void resolve(CombatContext& combatContext, const EffectParams& values) override;

  private:
    Target m_target;
};

#endif // GAINBLOCKEFFECT_H