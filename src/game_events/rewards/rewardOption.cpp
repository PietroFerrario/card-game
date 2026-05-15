#include "rewardOption.h"

RewardOption::RewardOption(std::string_view rewardOptionId, RewardOptionType rewardOptionType,
                           std::string_view description,
                           std::vector<std::unique_ptr<RewardEffect>> rewardEffectList)
    : m_rewardOptionId{rewardOptionId}, m_rewardOptionType{rewardOptionType},
      m_rewardOptionDescription{description}, m_rewardEffectList{std::move(rewardEffectList)}
{
}

const std::vector<std::unique_ptr<RewardEffect>>& RewardOption::getRewardEffectList() const
{
    return m_rewardEffectList;
}
