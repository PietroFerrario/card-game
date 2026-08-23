#include "eventGraph.h"
#include "entities/enemies/enemyId.h"
#include "eventSequence.h"
#include "gameConfig.h"
#include "game_events/matchEvent.h"
#include "game_events/matchEventData.h"
#include "game_events/storyEvent.h"
#include "game_events/storyEventData.h"

EventGraph::EventGraph(GameConfig& gameConfig, IMatchView& matchView, IRewardView& rewardView,
                       IProgressionView& progressionView, ICardFactory& cardFactory, Player& player)
    : m_gameConfig{gameConfig}, m_matchView{matchView}, m_rewardView{rewardView},
      m_progressionView{progressionView}, m_cardFactory{cardFactory}, m_player{player},
      m_enemyFactory{m_enemyLoader.loadEnemies()}
{
    m_cardFactory.registerCards();
    loadEvents();
}

void EventGraph::loadEvents()
{

    std::vector<EventData> eventDataList{m_matchEventLoader.loadEvents()};

    makeEvents(eventDataList);
}

void EventGraph::makeEvents(const std::vector<EventData>& list)
{
    for (const auto& eventData : list)
    {
        if (const auto* matchData = std::get_if<MatchEventData>(&eventData))
        {
            std::vector<RewardOption> eventRewardList{
                    m_rewardLoader.loadRewardList(matchData->rewardListId)};

            m_eventNodeList.emplace_back(std::make_unique<MatchEvent>(
                    m_gameConfig, m_matchView, m_rewardView, m_cardFactory, m_enemyFactory,
                    m_player, matchData->enemyId, std::move(eventRewardList)));
        }

        else if (const auto* storyData = std::get_if<StoryEventData>(&eventData))
        {
            std::vector<RewardOption> eventRewardList{
                    m_rewardLoader.loadRewardList(storyData->rewardListId)};

            m_eventNodeList.emplace_back(std::make_unique<StoryEvent>(
                    m_rewardView, m_cardFactory, storyData->storyId, storyData->title,
                    storyData->storyDescription, m_player, std::move(eventRewardList)));
        }
    }
}

EventNode EventGraph::makeNode(const std::vector<EventData>& list, const MatchEventData& matchData,
                               std::vector<RewardOption>& eventRewardList)
{

    MatchEvent event
    {
        std::make_unique<MatchEvent>(m_gameConfig, m_matchView, m_rewardView, m_cardFactory,
                                     m_enemyFactory, m_player, matchData.enemyId,
                                     std::move(eventRewardList))
    }
    return {}
}
