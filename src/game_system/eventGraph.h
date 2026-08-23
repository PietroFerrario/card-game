#ifndef EVENTGRAPH_H
#define EVENTGRAPH_H

#include "entities/enemies/enemyLoader.h"
#include "entities/player.h"
#include "eventNode.h"
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

class IProgressionView;

class EventGraph
{
  public:
    EventGraph(GameConfig& gameConfig, IMatchView& matchView, IRewardView& rewardView,
               IProgressionView& progressionView, ICardFactory& cardFactory, Player& player);

    void resolveEvent();

  private:
    void loadEvents();
    void makeMatchEvents(const std::vector<MatchEventData>& list);
    void makeEvents(const std::vector<EventData>& list);
    EventNode makeNode(const std::vector<EventData>& list, const MatchEventData& matchData,
                       std::vector<RewardOption>& eventRewardList);

    GameConfig& m_gameConfig;

    IMatchView& m_matchView;
    IRewardView& m_rewardView;

    Player& m_player;

    ICardFactory& m_cardFactory;
    MatchEventLoader m_matchEventLoader;
    RewardLoader m_rewardLoader;
    EnemyLoader m_enemyLoader;
    EnemyFactory m_enemyFactory;

    std::vector<EventNode> m_eventNodeList;
    int m_currentNode;

    IProgressionView& m_progressionView;
};

#endif // EVENTGRAPH_H