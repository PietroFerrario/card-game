#ifndef REWARDLOADER_H
#define REWARDLOADER_H

#include "rewardEffectData.h"
#include "rewardOption.h"
#include "rewardOptionData.h"

#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>

class RewardLoader
{
  public:
    RewardLoader();
    std::vector<RewardOption> RewardLoader::parseRewardsList();

  private:
    nlohmann::json m_data{};

    RewardOptionData loadRewardData(const json& reward);
    RewardEffectData loadRewardEffectData(const json& effectData);
    std::vector<UpgradeCardParam> loadUpgradeCardParams(const json& cardParams) {}

    inline static const std::unordered_map<std::string_view, RewardOptionType>
        m_rewardOptionTypeMap{{"equip", RewardOptionType::Equip},
                              {"economic", RewardOptionType::Economic},
                              {"gainCard", RewardOptionType::GainCard},
                              {"quest", RewardOptionType::Quest}};

    inline static const std::unordered_map<std::string_view, RewardEffectType>
        m_rewardEffectTypeMap{
            {"addCard", RewardEffectType::AddCard},
            {"addMoney", RewardEffectType::AddMoney},
            {"upgradeCard", RewardEffectType::UpgradeCard},
            {"registerQuest", RewardEffectType::RegisterQuest},
        };

    inline static const std::unordered_map<std::string_view, UpgradeCardParam>
        m_upgradeCardParamMap{{"", UpgradeCardParam::None},
                              {"attack", UpgradeCardParam::Attack},
                              {"armor", UpgradeCardParam::Armor},
                              {"action", UpgradeCardParam::Action},
                              {"drawing", UpgradeCardParam::Drawing}};
};

#endif // REWARDLOADER_H