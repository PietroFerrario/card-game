#include "rewardPhase.h"

#include "util/debug.h"

RewardPhase::RewardPhase(IRewardView& rewardView, Player& player, ICardFactory& cardFactory,
                         std::vector<RewardOption>& rewardOptionList)
    : m_rewardView{rewardView}, m_player{player}, m_cardFactory{cardFactory},
      m_rewardOptionList{rewardOptionList}, m_rewardContext{m_player, m_cardFactory, m_rewardView}
{
}

void RewardPhase::execute()
{
    DEBUG_LOG("Entering reward Phase");
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
    m_rewardView.showSelectedRewardDescription(selectedReward.getDescription());

    for (const auto& rewardEffectPtr : selectedReward.getRewardEffectList())
    {
        rewardEffectPtr->resolve(m_rewardContext);
    }
}

void RewardPhase::showRewardOptions()
{

    DEBUG_LOG("Showing the rewards options");

    m_rewardView.showRewardOptions(m_rewardOptionList);
}
