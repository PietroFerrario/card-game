#ifndef MATCHEVENTLOADER_H
#define MATCHEVENTLOADER_H

#include "deck/deckEntry.h"
#include "entities/enemies/enemyId.h"
#include "game_events/eventData.h"
#include "game_events/matchEventData.h"
#include "game_events/storyEventData.h"
#include <nlohmann/json.hpp>
#include <string_view>
#include <unordered_map>
#include <vector>

class MatchEventLoader
{
  public:
    MatchEventLoader();

    std::vector<EventData> loadEvents();

  private:
    nlohmann::json m_data{};
};

#endif // MATCHEVENTLOADER_H
