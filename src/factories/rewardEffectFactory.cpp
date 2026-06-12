#include "rewardEffectFactory.h"
#include "game_events/rewards/reward_effects/gainCardRewardEffect.h"
#include "game_events/rewards/reward_effects/gainMoneyRewardEffect.h"

#include <cassert>
#include <string_view>

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

std::unique_ptr<RewardEffect>
RewardEffectFactory::makeGainCardRewardEffect(const RewardEffectData& rewardEffectData)
{
    return std::make_unique<GainCardRewardEffect>(rewardEffectData.cardId);
}

std::unique_ptr<RewardEffect>
RewardEffectFactory::makeUpgradeCardRewardEffect(const RewardEffectData& rewardEffectData)
{
    return nullptr;
}
std::unique_ptr<RewardEffect>
RewardEffectFactory::makeChooseCardRewardEffect(const RewardEffectData& rewardEffectData)
{
    return nullptr;
}
std::unique_ptr<RewardEffect>
RewardEffectFactory::makeRegisterQuestRewardEffect(const RewardEffectData& rewardEffectData)
{
    return nullptr;
}
