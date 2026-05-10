#include "rewardPhase.h"

RewardPhase::RewardPhase(IRewardView& rewardView, std::vector<RewardOption>& rewardOptionList)
    : m_RewardView{rewardView}, m_rewardOptionList(rewardOptionList)
{
}