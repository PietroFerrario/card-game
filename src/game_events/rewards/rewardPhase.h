#ifndef REWARDPHASE_H
#define REWARDPHASE_H

#include "entities/player.h"
#include "rewardOption.h"
#include "ui/IRewardView.h"

#include <vector>

class RewardPhase
{
  public:
    explicit RewardPhase(IRewardView& rewardView, Player& player,
                         std::vector<RewardOption>& rewardOptionList);

    void execute();

  private:
    void getPlayerDecision();
    void showRewardOptions();
    void resolveReward();
    void resolveOptionEffects(int optionsIndex);

    Player& m_player;
    std::vector<RewardOption>& m_rewardOptionList;
    IRewardView& m_rewardView;
};

#endif // REWARDPHASE_H