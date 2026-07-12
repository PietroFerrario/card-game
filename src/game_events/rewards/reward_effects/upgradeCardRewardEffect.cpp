#include "upgradeCardRewardEffect.h"
#include "entities/player.h"
#include "factories/cardFactory.h"
#include "util/debug.h"

UpgradeCardRewardEffect::UpgradeCardRewardEffect(int amount,
                                                 std::vector<UpgradeCardParam> upgradeCardParam)
    : m_amount{amount}, m_upgradeCardParam{std::move(upgradeCardParam)}
{
}

void UpgradeCardRewardEffect::resolve(RewardContext& rewardContext)
{
    std::vector<std::unique_ptr<CardInstance>> deckToRender(
        generateDeckCardsForReward(rewardContext.cardFactory, rewardContext.player));

    std::vector<const CardInstance*> refDeckToRender;
    refDeckToRender.reserve(deckToRender.size());

    for (const std::unique_ptr<CardInstance>& currentCard : deckToRender)
    {
        refDeckToRender.emplace_back(currentCard.get());
    }

    rewardContext.rewardView.showRandomCardSelection(refDeckToRender);

    int selectedCard(
        rewardContext.rewardView.askPlayerSelectUpgradeCard(static_cast<int>(deckToRender.size())));

    rewardContext.player.getDeckPlayer().upgradeCard(
        rewardContext.player.getDeckPlayer().getCardEntry(selectedCard), m_amount,
        m_upgradeCardParam);

    DEBUG_LOG("Checking the effect of the upgrade. Enable or disable it with comments");
    // for debugging to check that it take effect
    // std::vector<std::unique_ptr<CardInstance>> updatedDeck(
    //     generateDeckCardsForReward(rewardContext.cardFactory, rewardContext.player));
    // std::vector<const CardInstance*> refUpdatedDeck;
    // refUpdatedDeck.reserve(updatedDeck.size());
    // for (const std::unique_ptr<CardInstance>& card : updatedDeck)
    //     refUpdatedDeck.emplace_back(card.get());
    // rewardContext.rewardView.showRandomCardSelection(refUpdatedDeck);
}

const std::vector<std::unique_ptr<CardInstance>>
UpgradeCardRewardEffect::generateDeckCardsForReward(ICardFactory& cardFactory, Player& player) const
{
    DEBUG_LOG("Entering generateDeckCardsForReward method");

    const std::vector<DeckEntry>& playerDeckCardEntries{player.getDeckPlayer().getCardList()};

    std::vector<std::unique_ptr<CardInstance>> deckCardsToDisplay;

    for (const auto& deckEntry : playerDeckCardEntries)
    {
        deckCardsToDisplay.emplace_back(cardFactory.makeSingleCard(deckEntry));
    }

    return deckCardsToDisplay;
}
