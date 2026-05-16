#include "rewardPhase.h"

#include "util/debug.h"

RewardPhase::RewardPhase(IRewardView& rewardView, Player& player, std::string_view enemyName,
                         std::vector<RewardOption>& rewardOptionList)
    : m_rewardView{rewardView}, m_player{player}, m_enemyName{enemyName},
      m_rewardOptionList{rewardOptionList}
{
}

void RewardPhase::execute()
{
    DEBUG_LOG("Entering reward Phase");
    m_rewardView.showRewardText(m_enemyName);
    showRewardOptions();

    RewardDecision decision{
        m_rewardView.askPlayerReward(static_cast<int>(m_rewardOptionList.size()))};

    if (decision.playerChoice == RewardChoice::SkipReward)
    {
        // implement skipping reward text
        DEBUG_LOG("Skipping rewards");
        m_rewardView.showSkippingReward();
    }
    else if (decision.playerChoice == RewardChoice::SelectReward)
    {
        DEBUG_LOG("Selecting rewards");
        DEBUG_LOG("Resolving rewards option effects");
        resolveOptionEffects(decision.selectedOption.value());
    }
    DEBUG_LOG("Finishing reward Phase");
}

void RewardPhase::resolveOptionEffects(int optionsIndex)
{
    RewardOption& selectedReward{m_rewardOptionList.at(optionsIndex)};
    m_rewardView.showSelectedReward(selectedReward.getName());

    for (const auto& rewardEffectPtr : selectedReward.getRewardEffectList())
    {
        rewardEffectPtr->resolve(m_player);
    }
}

void RewardPhase::showRewardOptions()
{

    DEBUG_LOG("Showing the rewards options");

    m_rewardView.showRewardOptions(m_rewardOptionList);
}
