#include "rewardOption.h"

RewardOption::RewardOption(std::string_view rewardOptionId, std::string_view rewardOptionName,
                           RewardOptionType rewardOptionType, std::string_view description,
                           std::vector<std::unique_ptr<RewardEffect>> rewardEffectList)
    : m_rewardOptionId{rewardOptionId}, m_rewardOptionName{rewardOptionName},
      m_rewardOptionType{rewardOptionType}, m_rewardOptionDescription{description},
      m_rewardEffectList{std::move(rewardEffectList)}
{
}

const std::vector<std::unique_ptr<RewardEffect>>& RewardOption::getRewardEffectList() const
{
    return m_rewardEffectList;
}

const std::string RewardOption::getRewardCardId() const
{
    assert(m_cardId.has_value() && "getRewardCardId called on a rewardOption with no CardId");
    return m_cardId.value();
}
