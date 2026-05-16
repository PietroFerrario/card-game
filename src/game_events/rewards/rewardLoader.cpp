#include "rewardLoader.h"

#include <cassert>
#include <fstream>
#include <string>

using json = nlohmann::json;

RewardLoader::RewardLoader()
{
    std::ifstream f("data/rewards_temp.json");
    assert(f.is_open() && "Failed to open rewards json");
    m_data = json::parse(f);
}

std::vector<RewardOption> RewardLoader::loadRewardList(std::string_view rewardListId)
{
    std::vector<RewardOption> rewardOptionList;

    const json& rewardLists = m_data.at("rewardLists");

    for (const auto& rewardList : rewardLists)
    {
        if (rewardList.at("rewardListId").get_ref<const std::string&>() == rewardListId)
        {
            for (const auto& rewardData : rewardList.at("rewards"))
            {
                rewardOptionList.emplace_back(
                    rewardListId, rewardData.at("rewardName").get_ref<const std::string&>(),
                    m_rewardOptionTypeMap.at(
                        rewardData.at("rewardType").get_ref<const std::string&>()),
                    rewardData.at("description").get_ref<const std::string&>(),
                    makeRewardEffectList(rewardData));
            }
            break;
        }
    }

    assert(!(rewardOptionList.empty()) && "RewardOptionList is empty, problem in loading it");
    return rewardOptionList;
}

std::vector<std::unique_ptr<RewardEffect>>
RewardLoader::makeRewardEffectList(const json& rewardData)
{
    std::vector<std::unique_ptr<RewardEffect>> effectList;
    for (const auto& effect : rewardData.at("effectList"))
    {
        effectList.emplace_back(
            m_rewardEffectFactory.makeRewardEffect(loadRewardEffectData(effect)));
    }

    return effectList;
}

RewardEffectData RewardLoader::loadRewardEffectData(const json& effectData)
{
    return {m_rewardEffectTypeMap.at(effectData.at("effectType").get_ref<const std::string&>()),
            effectData.at("amount").get<int>(),
            effectData.at("cardId").get_ref<const std::string&>(),
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