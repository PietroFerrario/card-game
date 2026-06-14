#ifndef CHOOSERANDOMCARDREWARDEFFECT_H
#define CHOOSERANDOMCARDREWARDEFFECT_H

#include "deck/deckPlayer.h"
#include "rewardEffect.h"

class ChooseRandomCardRewardEffect : public RewardEffect
{
  public:
    ChooseRandomCardRewardEffect(int amount) : m_amount{amount} {}

    void resolve(Player& player) override { player.getDeckPlayer() }

  private:
    int m_amount;
};

#endif // CHOOSERANDOMCARDREWARDEFFECT_H
