#ifndef REWARDPHASE_H
#define REWARDPHASE_H

#include "entities/player.h"
#include "rewardOption.h"
#include "ui/IRewardView.h"

#include <string_view>
#include <vector>

class RewardPhase
{
  public:
    explicit RewardPhase(IRewardView& rewardView, Player& player, std::string_view enemyName,
                         std::vector<RewardOption>& rewardOptionList);

    void execute();

  private:
    void getPlayerDecision();
    void showRewardOptions();
    void resolveReward();
    void resolveOptionEffects(int optionsIndex);

    Player& m_player;
    std::string_view m_enemyName;
    std::vector<RewardOption>& m_rewardOptionList;
    IRewardView& m_rewardView;
};

#endif // REWARDPHASE_H