#ifndef EVENTNODELOADER_H
#define EVENTNODELOADER_H

#include "deck/deckEntry.h"
#include "entities/enemies/enemyId.h"
#include "eventNodeData.h"
#include "game_events/eventData.h"
#include "game_events/matchEventData.h"
#include "game_events/storyEventData.h"

#include <nlohmann/json.hpp>
#include <string_view>
#include <unordered_map>
#include <vector>

class EventNodeLoader
{
  public:
    EventNodeLoader();

    std::vector<EventNodeData> loadEventNodes();

  private:
    MatchEventData loadMatchEvent(const nlohmann::json& matchData);
    StoryEventData loadStoryEvent(const nlohmann::json& storyData);

    nlohmann::json m_data{};
};

#endif // EVENTNODELOADER_H