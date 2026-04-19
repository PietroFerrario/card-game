#ifndef GAINMONEYREWARDEFFECT_H
#define GAINMONEYREWARDEFFECT_H

#include "rewardEffect.h"

class GainMoneyRewardEffect : public RewardEffect
{

  public:
    void GainMoneyRewardEffect::resolve() override { m_player.increaseMoney(m_amount); };

  private:
    int m_amount;
};

#endif // GAINMONEYREWARDEFFECT_H