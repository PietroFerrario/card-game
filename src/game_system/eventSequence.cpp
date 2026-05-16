#include "eventSequence.h"
#include "entities/enemies/enemyId.h"
#include "game_events/matchEvent.h"

EventSequence::EventSequence(IMatchView& matchView, IRewardView& rewardView, Player& player)
    : m_matchView{matchView}, m_rewardView{rewardView}, m_player{player}
{
}

void EventSequence::resolveEventSequence()
{
    for (auto& eventPtr : m_eventList)
    {
        eventPtr->resolve();
    }
}