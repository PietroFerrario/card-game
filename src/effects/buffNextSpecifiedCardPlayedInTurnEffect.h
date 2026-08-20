#ifndef BUFFNEXTSPECIFIEDCARDPLAYEDINTURNEFFECT_H
#define BUFFNEXTSPECIFIEDCARDPLAYEDINTURNEFFECT_H

#include "effect.h"

class BuffNextSpecifiedCardPlayedInTurnEffect : public Effect
{

  public:
    BuffNextSpecifiedCardPlayedInTurnEffect() = default;

    void resolve(CombatContext& combatContext, const CardParams& values) override;

  private:
};

#endif // BUFFNEXTSPECIFIEDCARDPLAYEDINTURNEFFECT_H
