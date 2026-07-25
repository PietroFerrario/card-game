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
        rewardContext.player.increasePopulation(m_amount);
    };

  private:
    int m_amount;
};

#endif // GAINPOPULATIONREWARDEFFECT_H
