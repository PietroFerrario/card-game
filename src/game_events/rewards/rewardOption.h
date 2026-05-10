#ifndef REWARDOPTION_H
#define REWARDOPTION_H

#include "factories/rewardEffectFactory.h"
#include "reward_effects/rewardEffect.h"

#include <memory>
#include <string>

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
    RewardOption(std::string_view rewardOptionId, RewardOptionType rewardOptionType,
                 std::string_view description, std::unique_ptr<RewardEffect> = nullptr);

  private:
    std::string m_rewardOptionId;
    RewardOptionType m_rewardOptionType;
    std::string m_description;
    std::unique_ptr<RewardEffect> m_rewardEffect;
};

#endif // REWARDOPTION_H