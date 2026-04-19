#ifndef REWARDEFFECT_H
#define REWARDEFFECT_H

#include "entities/player.h"
#include "rewardEffectData.h"

class RewardEffect
{
  public:
    virtual void resolve() = 0;

    virtual ~RewardEffect() = default;

  private:
  protected:
    Player& m_player;
};

#endif // REWARDEFFECT_H