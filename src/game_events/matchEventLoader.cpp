#include "matchEventLoader.h"
#include "gameEvent.h"

#include <fstream>

using json = nlohmann::json;

MatchEventLoader::MatchEventLoader()
{
    std::ifstream f("data/matches.json");
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
        match.rewardListId = matchList.at("rewardListId").get_ref<const std::string&>();

        matchEventDataList.emplace_back(match);
    }

    return matchEventDataList;
}
