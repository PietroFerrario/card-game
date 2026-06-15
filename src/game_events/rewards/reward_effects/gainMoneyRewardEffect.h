#ifndef GAINMONEYREWARDEFFECT_H
#define GAINMONEYREWARDEFFECT_H

#include "game_events/rewards/rewardContext.h"
#include "rewardEffect.h"

class GainMoneyRewardEffect : public RewardEffect
{

  public:
    GainMoneyRewardEffect(int amount) : m_amount{amount} {}

    void resolve(RewardContext& rewardContext) override
    {
        rewardContext.player.increaseMoney(m_amount);
    };

  private:
    int m_amount;
};

#endif // GAINMONEYREWARDEFFECT_H
