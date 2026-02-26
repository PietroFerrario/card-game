#ifndef LIMITCARDTOPLAYEFFECT_H
#define LIMITCARDTOPLAYEFFECT_H

#include "effect.h"

class LimitCardToPlayEffect : public Effect
{
  public:
    /**
     * @brief Constructs the effect with a fixed logical target.
     */
    LimitCardToPlayEffect() = default;

    /**
     * @brief Impose a limit on the number of cards the player can play this turn, using
     * CardParams::limitCards.
     *
     * @param combatContext Current combat execution context.
     * @param values Numeric parameters used during resolution.
     */
    void resolve(CombatContext& combatContext, const CardParams& values) override;

  private:
};

#endif // LIMITCARDTOPLAYEFFECT_H