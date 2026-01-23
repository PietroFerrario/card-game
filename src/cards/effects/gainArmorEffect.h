#ifndef GAINBLOCKEFFECT_H
#define GAINBLOCKEFFECT_H

#include "cards/effect.h"

/**
 * @brief Effect that grants armor to the player based on the card's armor value.
 *
 * Reads the card's current armor value and requests CardMatch to apply it.
 * Does not directly modify player state.
 */
class GainArmorEffect : public Effect
{
  public:
    /// @brief Applies the gain armor effect.
    void apply(CardMatch& card_match, CardInstance& card) override;

  private:
};

#endif // GAINBLOCKEFFECT_H