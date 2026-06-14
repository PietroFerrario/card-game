#include "rewardPhase.h"

#include "util/debug.h"

RewardPhase::RewardPhase(IRewardView& rewardView, Player& player, ICardFactory& cardFactory,
                         std::string_view enemyName, std::vector<RewardOption>& rewardOptionList)
    : m_rewardView{rewardView}, m_player{player}, m_cardFactory{cardFactory},
      m_enemyName{enemyName}, m_rewardOptionList{rewardOptionList}
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
    m_rewardView.showSelectedRewardDescription(selectedReward.getDescription());

    for (const auto& rewardEffectPtr : selectedReward.getRewardEffectList())
    {
        if (selectedReward.getRewardOptionType() == RewardOptionType::RandomCards)
        {
            // Restructure rewolve with a RewardContext!
            showRandomCardSelection(generateRandomCards()) m_rewardView.askPlayerSelectRewardCard()
        }

        rewardEffectPtr->resolve(m_player);
    }
}

void RewardPhase::askPlayerCardChoice() {}

std::vector<std::unique_ptr<CardInstance>> RewardPhase::generateRandomCards(int amount)
{
    const std::vector<std::string> registeredCardsList{m_cardFactory.getRegisteredCardsId()};
    std::vector<DeckEntry> randomDeckEntries;

    for (int i{0}; i < amount; i++)
    {
        randomDeckEntries.emplace_back(registeredCardsList.at(Random::get(0, amount - 1)));
    }

    std::vector<std::unique_ptr<CardInstance>> randomCardsToDisplay;
    for (const auto& deckEntry : randomDeckEntries)
    {
        randomCardsToDisplay.emplace_back(m_cardFactory.makeSingleCard(deckEntry));
    }

    return randomCardsToDisplay;
}

void RewardPhase::showRewardOptions()
{

    DEBUG_LOG("Showing the rewards options");

    m_rewardView.showRewardOptions(m_rewardOptionList);
}
