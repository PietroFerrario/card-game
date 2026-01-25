#ifndef GAINBLOCKEFFECT_H
#define GAINBLOCKEFFECT_H

#include "cards/effect.h"
#include "combat/combatTarget.h"

/**
 * @brief Effect that grants armor to the player based on the card's armor value.
 *
 * Reads the card's current armor value and requests CardMatch to apply it.
 * Does not directly modify player state.
 */
class GainArmorEffect : public Effect
{
  public:
    GainArmorEffect(Target target) : m_target{target} {}
    /// @brief Applies the gain armor effect.
    void resolve(CombatContext& combatContext, const EffectParams& values) override;

  private:
    Target m_target;
};

#endif // GAINBLOCKEFFECT_H