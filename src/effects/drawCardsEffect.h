#ifndef DRAWCARDEFFECT_H
#define DRAWCARDEFFECT_H

#include "effect.h"

/**
 * @brief Effect that draws cards into the actor's hand.
 *
 * DrawCardsEffect reads the draw amount from CardParams and requests that
 * number of cards to be drawn during effect resolution.
 *
 * The effect does not modify deck state directly; it requests the operation
 * through CombatContext.
 */
class DrawCardsEffect : public Effect
{
  public:
    /**
     * @brief Constructs a draw-cards effect.
     */
    DrawCardsEffect() = default;

    /**
     * @brief Draws cards using CardParams::drawing.
     *
     * @param combatContext Current combat execution context.
     * @param values Numeric parameters used during resolution.
     */
    void resolve(CombatContext& combatContext, const CardParams& values) override;

  private:
};

#endif // DRAWCARDEFFECT_H