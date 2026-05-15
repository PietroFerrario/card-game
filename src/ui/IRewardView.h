#ifndef IREWARDVIEW_H
#define IREWARDVIEW_H

#include "game_system/matchData.h"
#include "iotext.h"

#include <string>
#include <string_view>
#include <vector>

class RewardOption;

class IRewardView
{
  public:
    virtual ~IRewardView() = default;

    virtual void showRewardText(std::string_view enemyName) const = 0;
    virtual RewardDecision askPlayerReward(int limit) = 0;
    virtual void showSelectedReward(std::string_view rewardNameSelected) const = 0;

    virtual void showRewardOptions(const std::vector<RewardOption>& rewardListToRender) const = 0;
    virtual void showSkippingReward() const = 0;

  private:
};

#endif // IREWARDVIEW_H