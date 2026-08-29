#include "eventGraph.h"
#include "entities/enemies/enemyId.h"
#include "eventSequence.h"
#include "gameConfig.h"
#include "game_events/matchEvent.h"
#include "game_events/matchEventData.h"
#include "game_events/storyEvent.h"
#include "game_events/storyEventData.h"
#include "ui/IProgressionView.h"
#include "util/debug.h"

#include <cassert>

EventGraph::EventGraph(GameConfig& gameConfig, IMatchView& matchView, IRewardView& rewardView,
                       IProgressionView& progressionView, ICardFactory& cardFactory, Player& player)
    : m_gameConfig{gameConfig}, m_matchView{matchView}, m_rewardView{rewardView},
      m_progressionView{progressionView}, m_cardFactory{cardFactory}, m_player{player},
      m_enemyFactory{m_enemyLoader.loadEnemies()}
{
    m_cardFactory.registerCards();
    loadEventNodes();
}

void EventGraph::loadEventNodes()
{

    std::vector<EventNodeData> eventDataList{m_eventNodeLoader.loadEventNodes()};

    makeNodes(eventDataList);
}

void EventGraph::makeNodes(const std::vector<EventNodeData>& list)
{

    // build the map
    for (int i = 0; i < static_cast<int>(list.size()); ++i)
    {
        if (!m_idToIndexMap.emplace(list[i].id, i).second)
            DEBUG_LOG("Duplicate node id: " << list[i].id);
    }

    // build the nodes
    for (const auto& eventNodeData : list)
    {
        std::vector<int> nextList;
        for (const std::string& nextId : eventNodeData.next)
        {
            auto it = m_idToIndexMap.find(nextId);
            if (it == m_idToIndexMap.end())
            {

                DEBUG_LOG("Node " << eventNodeData.id << " references unknown id " << nextId);
                continue;
            }
            nextList.push_back(it->second);
        }
        m_eventNodeList.emplace_back(eventNodeData.id, makeEvent(eventNodeData.event),
                                     std::move(nextList), eventNodeData.previewDescription,
                                     eventNodeData.layer, eventNodeData.column);
    }
}

std::unique_ptr<GameEvent> EventGraph::makeEvent(const EventData& eventData)
{
    if (const auto* matchData = std::get_if<MatchEventData>(&eventData))
    {
        std::vector<RewardOption> eventRewardList{
                m_rewardLoader.loadRewardList(matchData->rewardListId)};

        return {std::make_unique<MatchEvent>(m_gameConfig, m_matchView, m_rewardView, m_cardFactory,
                                             m_enemyFactory, m_player, matchData->enemyId,
                                             std::move(eventRewardList))};
    }

    if (const auto* storyData = std::get_if<StoryEventData>(&eventData))
    {
        std::vector<RewardOption> eventRewardList{
                m_rewardLoader.loadRewardList(storyData->rewardListId)};

        return {std::make_unique<StoryEvent>(m_rewardView, m_cardFactory, storyData->storyId,
                                             storyData->title, storyData->storyDescription,
                                             m_player, std::move(eventRewardList))};
    }

    assert(false && "Unknown EventData alternative");
    std::terminate();
}

void EventGraph::resolveEvents()
{
    if (m_eventNodeList.empty())
    {
        DEBUG_LOG("Empty event graph");
        return;
    }

    while (true)
    {
        const EventNode& currentNode{m_eventNodeList.at(m_currentNode)};

        DEBUG_LOG("Resolving node " << currentNode.id);
        m_progressionView.showCurrentNode(currentNode.previewDescription, currentNode.layer);

        currentNode.event->resolve();

        if (currentNode.nextNodeList.empty())
        {
            DEBUG_LOG("Node " << currentNode.id << " has not following nodes. End of progression.");
            return;
        }

        std::vector<const EventNode*> options;
        options.reserve(currentNode.nextNodeList.size());

        for (const int nextIdex : currentNode.nextNodeList)
        {

            options.push_back(&m_eventNodeList.at(nextIdex));
        }

        m_progressionView.showProgressionTitle();
        m_progressionView.showPathOptions(options);

        int choice{-1};
        while (choice < 0)
        {
            choice = m_progressionView.askPlayerPath(static_cast<int>(options.size()));
        }

        m_progressionView.showSelectedPath(options.at(choice)->previewDescription);
        m_currentNode = currentNode.nextNodeList.at(choice);
    }
}
