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
        std::vector<DeckEntry> reward;
        for (const auto& singleReward : entry.at("reward"))
        {
            DeckEntry card{singleReward.at("cardId").get<std::string>(), 1};
            reward.emplace_back(card);
        }
        match.rewardCardsList = reward;

        matchEventDataList.emplace_back(match);
    }

    return matchEventDataList;
}
