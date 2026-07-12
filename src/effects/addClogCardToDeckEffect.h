#ifndef ADDCLOGCARDTODECK_H
#define ADDCLOGCARDTODECK_H

#include "effect.h"

class AddClogCardToDeckEffect : public Effect
{
  public:
    /**
     * @brief Constructs a AddClogCardToDeck effect.
     */
    AddClogCardToDeckEffect() = default;

    /**
     * @brief Adds a clog card to the deck of the player.
     *
     * @param combatContext Current combat execution context.
     * @param values Numeric parameters used during resolution (Number of cards).
     */
    void resolve(CombatContext& combatContext, const CardParams& values) override;
};

#endif // ADDCLOGCARDTODECK_H
