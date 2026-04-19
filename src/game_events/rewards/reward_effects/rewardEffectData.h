#ifndef REWARDEFFECTDATA_H
#define REWARDEFFECTDATA_H

#include "cards/cardParams.h"
#include <string>

enum class RewardEffectType
{
    AddCard,
    AddMoney,
    UpgradeCard
};

struct RewardEffectData
{
    RewardEffectType rewardEffectType;
    int amount{0};
    std::string cardId;
    std::string targetCardId;
    CardParams cardParams;
};

#endif // REWARDEFFECTDATA_H