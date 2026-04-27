#ifndef REWARDEFFECT_H
#define REWARDEFFECT_H

#include "entities/player.h"
#include "rewardEffectData.h"

class RewardEffect
{
  public:
    virtual void resolve(Player& player) = 0;

    virtual ~RewardEffect() = default;

  private:
};

#endif // REWARDEFFECT_H