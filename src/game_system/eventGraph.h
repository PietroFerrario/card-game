#ifndef EVENTGRAPH_H
#define EVENTGRAPH_H

#include "entities/enemies/enemyLoader.h"
#include "entities/player.h"
#include "factories/ICardFactory.h"
#include "factories/enemyFactory.h"
#include "game_events/eventNode.h"
#include "game_events/eventNodeLoader.h"
#include "game_events/gameEvent.h"
#include "game_events/rewards/rewardLoader.h"
#include "game_system/gameConfig.h"
#include "ui/IMatchView.h"
#include "ui/IProgressionView.h"
#include "ui/IRewardView.h"
#include <memory>
#include <unordered_map>
#include <vector>

class EventGraph
{
  public:
    EventGraph(GameConfig& gameConfig, IMatchView& matchView, IRewardView& rewardView,
               IProgressionView& progressionView, ICardFactory& cardFactory, Player& player);

    void resolveEvents();

  private:
    void loadEventNodes();
    void makeNodes(const std::vector<EventNodeData>& list);
    std::unique_ptr<GameEvent> makeEvent(const EventData& eventData);

    GameConfig& m_gameConfig;

    IMatchView& m_matchView;
    IRewardView& m_rewardView;
    IProgressionView& m_progressionView;

    Player& m_player;

    ICardFactory& m_cardFactory;
    EventNodeLoader m_eventNodeLoader;
    RewardLoader m_rewardLoader;
    EnemyLoader m_enemyLoader;
    EnemyFactory m_enemyFactory;

    std::vector<EventNode> m_eventNodeList;
    std::unordered_map<std::string, int> m_idToIndexMap;
    int m_currentNode{0};
};

#endif // EVENTGRAPH_H