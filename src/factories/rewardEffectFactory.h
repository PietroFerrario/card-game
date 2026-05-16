#ifndef REWARDEFFECTFACTORY_H
#define REWARDEFFECTFACTORY_H

#include <nlohmann/json.hpp>
#include <unordered_map>

#include "game_events/rewards/reward_effects/rewardEffect.h"
#include "game_events/rewards/reward_effects/rewardEffectData.h"

class RewardEffectFactory
{
  public:
    RewardEffectFactory() = default;

    std::unique_ptr<RewardEffect> makeRewardEffect(const RewardEffectData& rewardEffectData);

  private:
    static std::unique_ptr<RewardEffect>
    makeGainMoneyRewardEffect(const RewardEffectData& rewardEffectData);
    static std::unique_ptr<RewardEffect>
    makeGainCardRewardEffect(const RewardEffectData& rewardEffectData);
    static std::unique_ptr<RewardEffect>
    makeUpgradeCardRewardEffect(const RewardEffectData& rewardEffectData);
    static std::unique_ptr<RewardEffect>
    makeChooseCardRewardEffect(const RewardEffectData& rewardEffectData);
    static std::unique_ptr<RewardEffect>
    makeRegisterQuestRewardEffect(const RewardEffectData& rewardEffectData);

    inline static const std::unordered_map<RewardEffectType,
                                           std::unique_ptr<RewardEffect> (*)(
                                               const RewardEffectData& rewardEffectData)>
        m_rewardEffectMap{{RewardEffectType::GainMoney, makeGainMoneyRewardEffect},
                          {RewardEffectType::GainCard, makeGainCardRewardEffect},
                          {RewardEffectType::UpgradeCard, makeUpgradeCardRewardEffect},
                          {RewardEffectType::ChooseCards, makeChooseCardRewardEffect},
                          {RewardEffectType::RegisterQuest, makeRegisterQuestRewardEffect}};
};

#endif // REWARDEFFECTFACTORY_H