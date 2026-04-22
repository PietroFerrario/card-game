#include "rewardLoader.h"

#include <fstream>
#include <string>

using json = nlohmann::json;

RewardLoader::RewardLoader()
{
    std::ifstream f("data/rewards.json");
    m_data = json::parse(f);
}

std::vector<RewardOption> RewardLoader::parseRewardsList()
{
    std::vector<RewardOption> rewardOptionList;

    const json& rewardList = m_data.at("rewardsList");

    for (const auto& rewardData : rewardList)
    {
        RewardOptionData rewardOptionData{std::move(loadRewardData(rewardData))};

        // Construct the RewardOption now with the factory!
    }
}

RewardOptionData RewardLoader::loadRewardData(const json& rewardData)
{
    return {rewardData.at("id").get_ref<const std::string&>(),
            m_rewardOptionTypeMap.at(rewardData.at("rewardType").get_ref<const std::string&>()),
            rewardData.at("description").get_ref<const std::string&>(),
            loadRewardEffectData(rewardData.at("effect"))};
}

RewardEffectData RewardLoader::loadRewardEffectData(const json& effectData)
{
    return {m_rewardEffectTypeMap.at(effectData.at("effectType").get_ref<const std::string&>()),
            effectData.at("amount").get<int>(),
            effectData.at("cardId").get_ref<const std::string&>(),
            effectData.at("targetCardId").get_ref<const std::string&>(),
            loadUpgradeCardParams(effectData.at("upgradeCardParams"))};
}

std::vector<UpgradeCardParam> RewardLoader::loadUpgradeCardParams(const json& cardParams)
{
    std::vector<UpgradeCardParam> paramList;
    for (auto const& param : cardParams)
    {
        paramList.emplace_back(m_upgradeCardParamMap.at(param.get_ref<const std::string&>()));
    }
    return paramList;
}