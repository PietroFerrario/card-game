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
        auto player{rewardContext.player};
        player.increaseMoney(m_amount);

        rewardContext.rewardView.showNumbericalGainSummaryEffect(m_amount, player.getMoney(),
                                                                 m_resource);
    }

  private:
    int m_amount;
    std::string m_resource{"gold"};
};

#endif // GAINMONEYREWARDEFFECT_H
