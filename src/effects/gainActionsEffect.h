#ifndef GAINACTIONSEFFECT_H
#define GAINACTIONSEFFECT_H

#include "effect.h"

/**
 * @brief Effect that grants additional actions for the current turn.
 *
 * GainActionsEffect reads the action amount from CardParams and increases
 * the actor's available actions for the current turn.
 *
 * The effect does not modify turn state directly; it requests the operation
 * through CombatContext.
 */
class GainActionsEffect : public Effect
{
  public:
    /**
     * @brief Constructs a gain-actions effect.
     */
    GainActionsEffect() = default;

    /**
     * @brief Grants actions using CardParams::actions.
     *
     * @param combatContext Current combat execution context.
     * @param values Numeric parameters used during resolution.
     */
    void resolve(CombatContext& combatContext, const CardParams& values) override;

  private:
};

#endif // GAINACTIONEFFECT_H
