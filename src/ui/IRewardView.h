#ifndef IREWARDVIEW_H
#define IREWARDVIEW_H

#include "game_system/matchData.h"
#include "iotext.h"

#include <string>
#include <string_view>
#include <vector>

class IRewardView
{
  public:
    virtual ~IRewardView() = default;

    virtual void showRewardText(std::string_view enemyName) const = 0;
    virtual RewardDecision askPlayerReward(int limit) = 0;
    virtual void showReward(std::string_view cardSelected) const = 0;

  private:
};

#endif // IREWARDVIEW_H