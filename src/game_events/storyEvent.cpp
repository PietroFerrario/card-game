#include "storyEvent.h"
#include "game_events/rewards/rewardPhase.h"
#include "util/debug.h"

StoryEvent::StoryEvent(IRewardView& rewardView, ICardFactory& cardFactory, std::string storyId,
                       std::string title, std::string storyDescription, Player& player,
                       std::vector<RewardOption> rewardOptionList)
    : m_rewardView{rewardView}, m_cardFactory{cardFactory}, m_storyId{storyId}, m_title{title},
      m_storyDescription{storyDescription}, m_player{player},
      m_rewardOptionList{std::move(rewardOptionList)}
{
}

void StoryEvent::resolve()
{
    DEBUG_LOG("Entering Story Event");
    m_rewardView.showStoryEventTitle(m_title);
    m_rewardView.showStoryEventDescription(m_storyDescription);
    RewardPhase rewardPhase{m_rewardView, m_player, m_cardFactory, m_rewardOptionList};
    rewardPhase.execute();
}
