#ifndef UPGRADECARDREWARDEFFECT_H
#define UPGRADECARDREWARDEFFECT_H

#include "cards/cardInstance.h"
#include "deck/deckPlayer.h"
#include "game_events/rewards/rewardContext.h"
#include "rewardEffect.h"

#include <memory>
#include <vector>

class UpgradeCardRewardEffect : public RewardEffect
{
  public:
    UpgradeCardRewardEffect(int amount);
    void resolve(RewardContext& rewardContext) override;

  private:
    const std::vector<std::unique_ptr<CardInstance>>
    generateDeckCardsForReward(ICardFactory& cardFactory, Player& player) const;

    std::vector<UpgradeCardParam> m_upgradeCardParam;
    int m_amount;
};

#endif // UPGRADECARDREWARDEFFECT_H
