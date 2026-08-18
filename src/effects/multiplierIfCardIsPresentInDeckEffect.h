#ifndef MULTIPLIERIFCARDISPRESENTINDECKEFFECT_H
#define MULTIPLIERIFCARDISPRESENTINDECKEFFECT_H

#include "combat/combatTarget.h"

#include "effect.h"

class MultiplierIfCardIsPresentInDeckEffect : public Effect
{

  public:
    MultiplierIfCardIsPresentInDeckEffect() = default;

    void resolve(CombatContext& combatContext, const CardParams& values) override;

  private:
};

#endif // MULTIPLIERIFCARDISPRESENTINDECKEFFECT_H