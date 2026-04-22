#ifndef REWARDOPTIONDATA_H
#define REWARDOPTIONDATA_H

#include "reward_effects/rewardEffectData.h"

#include <string>
#include <vector>

enum class RewardOptionType
{
    Equip,
    Quest,
    Economic,
    GainCard
};

struct RewardOptionData
{
    std::string rewardId;
    RewardOptionType rewardOptionType;
    std::string description;
    RewardEffectData rewardEffectData;
};

#endif // REWARDOPTIONDATA_H