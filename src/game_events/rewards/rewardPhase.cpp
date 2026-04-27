#include "rewardPhase.h"

explicit RewardPhase::RewardPhase(std::vector<RewardOption> rewardOptionList)
    : m_rewardOptionList(std::move(rewardOptionList))
{
}