#ifndef GAINPOPULATIONREWARDEFFECT_H
#define GAINPOPULATIONREWARDEFFECT_H

#include "game_events/rewards/rewardContext.h"
#include "rewardEffect.h"

class GainPopulationRewardEffect : public RewardEffect
{

  public:
    GainPopulationRewardEffect(int amount) : m_amount{amount} {}

    void resolve(RewardContext& rewardContext) override
    {
        auto player{rewardContext.player};
        player.increasePopulation(m_amount);
        rewardContext.rewardView.showNumbericalGainSummaryEffect(m_amount, player.getPopulation(),
                                                                 m_resource);
    };

  private:
    int m_amount;
    std::string m_resource{"population"};
};

#endif // GAINPOPULATIONREWARDEFFECT_H
