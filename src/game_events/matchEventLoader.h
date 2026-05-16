#ifndef MATCHEVENTLOADER_H
#define MATCHEVENTLOADER_H

#include "deck/deckEntry.h"
#include "entities/enemies/enemyId.h"
#include "game_events/matchEventData.h"

#include <nlohmann/json.hpp>
#include <string_view>
#include <unordered_map>
#include <vector>

class MatchEventLoader
{
  public:
    MatchEventLoader();

    std::vector<MatchEventData> loadMatches();

  private:
    nlohmann::json m_data{};
    inline static const std::unordered_map<std::string, EnemyId> m_enemyIdMap{
        {"Bandits", EnemyId::Bandits}, {"Monster", EnemyId::Monster}};
};

#endif // MATCHEVENTLOADER_H