#ifndef EVENTSEQUENCE_H
#define EVENTSEQUENCE_H

#include "entities/player.h"
#include "game_events/gameEvent.h"
#include "game_events/matchEventLoader.h"
#include "game_events/rewards/rewardLoader.h"
#include "ui/IMatchView.h"
#include "ui/IRewardView.h"

#include <memory>
#include <vector>

class EventSequence
{
  public:
    EventSequence(IMatchView& IMatchView, IRewardView& rewardView, Player& player);

    void loadMatchEvents();

    void resolveEventSequence();

  private:
    void makeMatchEvents(const std::vector<MatchEventData>& list);

    IMatchView& m_matchView;
    IRewardView& m_rewardView;

    Player& m_player;

    MatchEventLoader m_matchEventLoader;
    RewardLoader m_rewardLoader;
    std::vector<std::unique_ptr<GameEvent>> m_eventList;
};

#endif // EVENTSEQUENCE_H