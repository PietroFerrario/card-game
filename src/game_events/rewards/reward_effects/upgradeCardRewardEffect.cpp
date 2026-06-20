#include "upgradeCardRewardEffect.h"
#include "entities/player.h"
#include "factories/cardFactory.h"
#include "util/debug.h"

UpgradeCardRewardEffect::UpgradeCardRewardEffect(int amount) : m_amount{amount} {}

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

    int selectedCard(rewardContext.rewardView.askPlayerSelectRewardCard(m_amount));
}

const std::vector<std::unique_ptr<CardInstance>>
UpgradeCardRewardEffect::generateDeckCardsForReward(ICardFactory& cardFactory, Player& player) const
{
    DEBUG_LOG("Entering generateDeckCardsForReward method");

    const std::vector<DeckEntry> playerDeckCardEntries{player.getDeckPlayer().getCardList()};

    std::vector<std::unique_ptr<CardInstance>> deckCardsToDisplay;

    for (const auto& deckEntry : playerDeckCardEntries)
    {
        deckCardsToDisplay.emplace_back(cardFactory.makeSingleCard(deckEntry));
    }

    return deckCardsToDisplay;
}
