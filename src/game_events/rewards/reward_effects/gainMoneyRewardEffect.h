#ifndef GAINMONEYREWARDEFFECT_H
#define GAINMONEYREWARDEFFECT_H

#include "rewardEffect.h"

class GainMoneyRewardEffect : public RewardEffect
{

  public:
    GainMoneyRewardEffect(int amount) : m_amount{amount} {}

    void resolve(Player& player) override { player.increaseMoney(m_amount); };

  private:
    int m_amount;
};

#endif // GAINMONEYREWARDEFFECT_H