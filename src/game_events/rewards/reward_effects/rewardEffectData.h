#ifndef REWARDEFFECTDATA_H
#define REWARDEFFECTDATA_H

#include "cards/cardParams.h"
#include <string>
#include <vector>

enum class RewardEffectType
{
    GainCard,
    GainMoney,
    UpgradeCard,
    RegisterQuest,
    ChooseCards,
};

enum class UpgradeCardParam
{
    None,
    Attack,
    Armor,
    Action,
    Drawing,
};

struct RewardEffectData
{
    RewardEffectType rewardEffectType;
    int amount{0};
    std::string cardId;
    std::vector<UpgradeCardParam> upgradeCardParam{UpgradeCardParam::None};
};

#endif // REWARDEFFECTDATA_H
