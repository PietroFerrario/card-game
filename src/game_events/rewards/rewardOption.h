#ifndef REWARDOPTION_H
#define REWARDOPTION_H

#include "factories/rewardEffectFactory.h"
#include "reward_effects/rewardEffect.h"

#include <memory>
#include <string>
#include <string_view>
#include <vector>

enum class RewardOptionType
{
    Equip,
    Quest,
    Economic,
    GainCard
};

class RewardOption
{
  public:
    RewardOption(std::string_view rewardOptionId, std::string_view rewardOptionName,
                 RewardOptionType rewardOptionType, std::string_view description,
                 std::vector<std::unique_ptr<RewardEffect>> rewardEffectList = {});

    std::string_view getName() const { return m_rewardOptionName; }
    std::string_view getDescription() const { return m_rewardOptionDescription; }
    const std::vector<std::unique_ptr<RewardEffect>>& getRewardEffectList() const;

  private:
    std::string m_rewardOptionId;
    std::string m_rewardOptionName;
    RewardOptionType m_rewardOptionType;
    std::string m_rewardOptionDescription;
    std::vector<std::unique_ptr<RewardEffect>> m_rewardEffectList{};
};

#endif // REWARDOPTION_H