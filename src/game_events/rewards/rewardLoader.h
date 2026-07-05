#ifndef REWARDLOADER_H
#define REWARDLOADER_H

#include "cards/cardParams.h"
#include "factories/rewardEffectFactory.h"
#include "rewardOption.h"
#include "reward_effects/rewardEffectData.h"

#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>

class RewardLoader
{
  public:
    RewardLoader();
    std::vector<RewardOption> loadRewardList(std::string_view rewardListName);

  private:
    nlohmann::json m_data{};
    RewardEffectFactory m_rewardEffectFactory;

    RewardEffectData loadRewardEffectData(const nlohmann::json& effectData);
    std::vector<std::unique_ptr<RewardEffect>>
    makeRewardEffectList(const nlohmann::json& effectData);
    std::vector<UpgradeCardParam> loadUpgradeCardParams(const nlohmann::json& cardParams);

    inline static const std::unordered_map<std::string_view, RewardOptionType>
        m_rewardOptionTypeMap{{"equip", RewardOptionType::Equip},
                              {"economic", RewardOptionType::Economic},
                              {"upgradeDeck", RewardOptionType::UpgradeDeck},
                              {"quest", RewardOptionType::Quest},
                              {"randomCards", RewardOptionType::RandomCards}};

    inline static const std::unordered_map<std::string_view, RewardEffectType>
        m_rewardEffectTypeMap{
            {"gainCard", RewardEffectType::GainCard},
            {"gainMoney", RewardEffectType::GainMoney},
            {"upgradeCard", RewardEffectType::UpgradeCard},
            {"cardChoice", RewardEffectType::ChooseCards},
            {"registerQuest", RewardEffectType::RegisterQuest},
        };

    inline static const std::unordered_map<std::string_view, UpgradeCardParam>
        m_upgradeCardParamMap{{"attack", UpgradeCardParam::Attack},
                              {"armor", UpgradeCardParam::Armor},
                              {"action", UpgradeCardParam::Action},
                              {"drawing", UpgradeCardParam::Drawing}};
};

#endif // REWARDLOADER_H
