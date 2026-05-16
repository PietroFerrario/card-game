#include "eventSequence.h"
#include "entities/enemies/enemyId.h"
#include "game_events/matchEvent.h"
#include "game_events/matchEventData.h"

EventSequence::EventSequence(IMatchView& matchView, IRewardView& rewardView, Player& player)
    : m_matchView{matchView}, m_rewardView{rewardView}, m_player{player}
{
    loadMatchEvents();
}

void EventSequence::loadMatchEvents()
{

    std::vector<MatchEventData> matchEventDataList{m_matchEventLoader.loadMatches()};

    makeMatchEvents(matchEventDataList);
}

void EventSequence::makeMatchEvents(const std::vector<MatchEventData>& list)
{
    for (const auto& matchEventData : list)
    {
        std::vector<RewardOption> matchEvenRewardList{
            m_rewardLoader.loadRewardList(matchEventData.rewardListId)};

        m_eventList.emplace_back(std::make_unique<MatchEvent>(m_matchView, m_rewardView, m_player,
                                                              matchEventData.enemyId,
                                                              std::move(matchEvenRewardList)));
    }
}

void EventSequence::resolveEventSequence()
{
    for (auto& eventPtr : m_eventList)
    {
        eventPtr->resolve();
    }
}