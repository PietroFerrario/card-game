#include "rewardOption.h"

RewardOption::RewardOption(std::string_view rewardOptionId, RewardOptionType rewardOptionType,
                           std::string_view description, std::unique_ptr<RewardEffect> rewardEffect)
    : m_rewardOptionId{rewardOptionId}, m_rewardOptionType{rewardOptionType},
      m_description{description}, m_rewardEffect{std::move(rewardEffect)}
{
}