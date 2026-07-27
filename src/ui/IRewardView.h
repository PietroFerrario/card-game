#ifndef IREWARDVIEW_H
#define IREWARDVIEW_H

#include "cards/cardInstance.h"
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
    virtual void showSelectedRewardDescription(std::string_view rewardDescription) const = 0;

    virtual void showRewardOptions(const std::vector<RewardOption>& rewardListToRender) const = 0;
    virtual void showSkippingReward() const = 0;

    virtual int askPlayerSelectRewardCard(int limit) = 0;
    virtual int askPlayerSelectUpgradeCard(int limit) = 0;
    virtual void
    showRandomCardSelection(const std::vector<const CardInstance*>& handToRender) const = 0;

    virtual void showStoryEventTitle(std::string_view enemyName) const = 0;
    virtual void showStoryEventDescription(std::string_view storyEventDescription) const = 0;
    virtual void showNumbericalGainSummaryEffect(int increase, int total,
                                                 std::string_view resource) const = 0;

    virtual void showAddedCard(std::string_view cardName, int deckSize) const = 0;

  private:
};

#endif // IREWARDVIEW_H
