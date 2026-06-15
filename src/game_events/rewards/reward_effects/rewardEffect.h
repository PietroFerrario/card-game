#ifndef REWARDEFFECT_H
#define REWARDEFFECT_H

#include "game_events/rewards/rewardContext.h"
#include "rewardEffectData.h"

class RewardEffect
{
  public:
    virtual void resolve(RewardContext& rewardContext) = 0;

    virtual ~RewardEffect() = default;

  private:
};

#endif // REWARDEFFECT_H
