#include "rewardEffectFactory.h"
#include "game_events/rewards/reward_effects/gainMoneyRewardEffect.h"

#include <cassert>

std::unique_ptr<RewardEffect>
RewardEffectFactory::makeRewardEffect(const RewardEffectData& rewardEffectData)
{
    auto mapIter = m_rewardEffectMap.find(rewardEffectData.rewardEffectType);

    if (mapIter == m_rewardEffectMap.end())
    {
        assert(false && "Unknown reward effect specifier");
        std::terminate();
    }

    return mapIter->second(rewardEffectData);
}

std::unique_ptr<RewardEffect>
RewardEffectFactory::makeGainMoneyRewardEffect(const RewardEffectData& rewardEffectData)
{
    return std::make_unique<GainMoneyRewardEffect>(rewardEffectData.amount);
}