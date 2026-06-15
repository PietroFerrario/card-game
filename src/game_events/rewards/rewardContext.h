#ifndef REWARDCONTEXT_H
#define REWARDCONTEXT_H

#include "entities/player.h"
#include "factories/ICardFactory.h"
#include "ui/IRewardView.h"

struct RewardContext
{
    Player& player;
    ICardFactory& cardFactory;
    IRewardView& rewardView;
};

#endif // REWARDCONTEXT_H
