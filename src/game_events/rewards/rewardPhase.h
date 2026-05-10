#ifndef REWARDPHASE_H
#define REWARDPHASE_H

#include "rewardOption.h"
#include "ui/IRewardView.h"

#include <vector>

class RewardPhase
{
  public:
    explicit RewardPhase(IRewardView& rewardView, std::vector<RewardOption>& rewardOptionList);

    void showRewardOptions();

    void resolveReward();

  private:
    std::vector<RewardOption>& m_rewardOptionList;
    IRewardView& m_RewardView;
};

#endif // REWARDPHASE_H