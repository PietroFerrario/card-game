#include "matchEventLoader.h"
#include "gameEvent.h"

#include <cassert>
#include <fstream>

using json = nlohmann::json;

MatchEventLoader::MatchEventLoader()
{
    std::ifstream f("data/matchList.json");
    assert(f.is_open() && "Failed to open matches json");
    m_data = json::parse(f);
}

std::vector<MatchEventData> MatchEventLoader::loadMatches()
{

    const json& matchList = m_data.at("matchList");

    std::vector<MatchEventData> matchEventDataList;

    for (const auto& entry : matchList)
    {
        MatchEventData match;
        match.enemyId = m_enemyIdMap.at(entry.at("enemyId").get_ref<const std::string&>());
        match.rewardListId = entry.at("rewardListId").get_ref<const std::string&>();

        matchEventDataList.emplace_back(match);
    }

    return matchEventDataList;
}
