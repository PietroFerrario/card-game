#include "chooseRandomCardRewardEffect.h"
#include "cards/cardDefinition.h"
#include "factories/cardFactory.h"
#include "util/Random.h"
#include "util/debug.h"
ChooseRandomCardRewardEffect::ChooseRandomCardRewardEffect(int amount) : m_amount{amount} {}

void ChooseRandomCardRewardEffect::resolve(RewardContext& rewardContext)
{
    std::vector<std::unique_ptr<CardInstance>> randomCardToRender(
        generateRandomCards(rewardContext.cardFactory));

    std::vector<const CardInstance*> refRandomCardToRender;
    refRandomCardToRender.reserve(randomCardToRender.size());

    for (const std::unique_ptr<CardInstance>& currentCard : randomCardToRender)
    {
        refRandomCardToRender.emplace_back(currentCard.get());
    }

    rewardContext.rewardView.showRandomCardSelection(refRandomCardToRender);

    int selectedCard(rewardContext.rewardView.askPlayerSelectRewardCard(m_amount));

    rewardContext.player.addCardToDeck(
        randomCardToRender.at(selectedCard)->getCardDefinition().getID(),
        randomCardToRender.at(selectedCard)->getCardDefinition().getCardPopulation());
}

std::vector<std::unique_ptr<CardInstance>>
ChooseRandomCardRewardEffect::generateRandomCards(ICardFactory& cardFactory) const
{
    DEBUG_LOG("Entering generatingRandomCards method");
    const std::vector<std::string> registeredCardsList{cardFactory.getRegisteredCardsId()};
    std::vector<DeckEntry> randomDeckEntries;

    for (int i{0}; i < m_amount; i++)
    {
        randomDeckEntries.emplace_back(registeredCardsList.at(
            Random::get(0, static_cast<int>(registeredCardsList.size()) - 1)));
    }

    std::vector<std::unique_ptr<CardInstance>> randomCardsToDisplay;
    for (const auto& deckEntry : randomDeckEntries)
    {
        randomCardsToDisplay.emplace_back(cardFactory.makeSingleCard(deckEntry));
    }

    return randomCardsToDisplay;
}
