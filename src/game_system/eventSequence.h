#ifndef EVENTSEQUENCE_H
#define EVENTSEQUENCE_H

#include "entities/player.h"
#include "factories/ICardFactory.h"
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
    EventSequence(IMatchView& IMatchView, IRewardView& rewardView, ICardFactory& cardFactory,
                  Player& player);

    void resolveEventSequence();

  private:
    void loadMatchEvents();
    void makeMatchEvents(const std::vector<MatchEventData>& list);

    IMatchView& m_matchView;
    IRewardView& m_rewardView;

    Player& m_player;

    ICardFactory& m_cardFactory;
    MatchEventLoader m_matchEventLoader;
    RewardLoader m_rewardLoader;
    std::vector<std::unique_ptr<GameEvent>> m_eventList;
};

#endif // EVENTSEQUENCE_H
