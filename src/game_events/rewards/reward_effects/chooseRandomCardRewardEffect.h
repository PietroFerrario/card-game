#ifndef CHOOSERANDOMCARDREWARDEFFECT_H
#define CHOOSERANDOMCARDREWARDEFFECT_H

#include "cards/cardInstance.h"
#include "deck/deckPlayer.h"
#include "game_events/rewards/rewardContext.h"
#include "rewardEffect.h"

#include <memory>
#include <vector>

class ChooseRandomCardRewardEffect : public RewardEffect
{
  public:
    ChooseRandomCardRewardEffect(int amount);
    void resolve(RewardContext& rewardContext) override;

  private:
    const std::vector<std::unique_ptr<CardInstance>>
    generateRandomCards(ICardFactory& cardFactory) const;

    int m_amount;
};

#endif // CHOOSERANDOMCARDREWARDEFFECT_H
