#ifndef STORYEVENT_H
#define STORYEVENT_H

#include "entities/player.h"
#include "factories/enemyFactory.h"
#include "gameEvent.h"
#include "ui/IRewardView.h"

#include <string>
#include <vector>

class StoryEvent : public GameEvent
{
  public:
    StoryEvent(IRewardView& rewardView, ICardFactory& cardFactory, std::string storyId,
               std::string title, std::string storyDescription, Player& player,
               std::vector<RewardOption> rewardOptionList);
    void resolve() override;

  private:
    IRewardView& m_rewardView;
    ICardFactory& m_cardFactory;

    std::string m_storyId;
    std::string m_title;
    Player& m_player;
    std::string m_storyDescription;
    std::vector<RewardOption> m_rewardOptionList;
};

#endif // STORYEVENT_H
