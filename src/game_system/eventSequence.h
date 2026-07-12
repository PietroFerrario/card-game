#ifndef EVENTSEQUENCE_H
#define EVENTSEQUENCE_H

#include "entities/enemies/enemyLoader.h"
#include "entities/player.h"
#include "factories/ICardFactory.h"
#include "factories/enemyFactory.h"
#include "game_events/gameEvent.h"
#include "game_events/matchEventLoader.h"
#include "game_events/rewards/rewardLoader.h"
#include "game_system/gameConfig.h"
#include "ui/IMatchView.h"
#include "ui/IRewardView.h"
#include <memory>
#include <vector>

class EventSequence
{
  public:
    EventSequence(GameConfig& gameConfig, IMatchView& IMatchView, IRewardView& rewardView,
                  ICardFactory& cardFactory, Player& player);

    void resolveEventSequence();

  private:
    void loadEvents();
    void makeMatchEvents(const std::vector<MatchEventData>& list);
    void makeEvents(const std::vector<EventData>& list);

    GameConfig& m_gameConfig;

    IMatchView& m_matchView;
    IRewardView& m_rewardView;

    Player& m_player;

    ICardFactory& m_cardFactory;
    MatchEventLoader m_matchEventLoader;
    RewardLoader m_rewardLoader;
    EnemyLoader m_enemyLoader;
    EnemyFactory m_enemyFactory;
    std::vector<std::unique_ptr<GameEvent>> m_eventList;
};

#endif // EVENTSEQUENCE_H
