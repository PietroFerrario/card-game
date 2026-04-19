#include "rewardLoader.h"

#include <fstream>
#include <string>

using json = nlohmann::json;

RewardLoader::RewardLoader()
{
    std::ifstream f("data/rewards.json");
    m_data = json::parse(f);
}

std::vector<RewardOption> RewardLoader::loadRewards()
{
    std::vector<RewardOption> rewardOptionList;

    const json& rewardList = m_data.at("rewardsList");

    for (const auto& reward : rewardList)
    {
    }
}