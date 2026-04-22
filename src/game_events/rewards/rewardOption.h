#ifndef REWARDOPTION_H
#define REWARDOPTION_H

#include "factories/rewardEffectFactory.h"
#include "rewardEffect.h"
#include "rewardOptionData.h"

#include <string>

class RewardOption
{
  public:
  private:
    std::string m_rewardOptionId;
    RewardOptionType m_rewardOptionType;
    std::string m_description;
    RewardEffectFactory m_rewardEffectFactory;
};

#endif // REWARDOPTION_H