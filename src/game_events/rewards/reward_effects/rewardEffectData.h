#ifndef REWARDEFFECTDATA_H
#define REWARDEFFECTDATA_H

#include "cards/cardParams.h"
#include <string>
#include <vector>

enum class RewardEffectType
{
    GainCard,
    GainMoney,
    GainPopulation,
    UpgradeCard,
    RegisterQuest,
    ChooseCards,
};

struct RewardEffectData
{
    RewardEffectType rewardEffectType;
    int amount{0};
    std::string cardId;
    std::vector<UpgradeCardParam> upgradeCardParam;
};

#endif // REWARDEFFECTDATA_H
