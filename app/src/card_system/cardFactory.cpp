#include "cardFactory.h"
#include "util/debug.h"
#include "cardInstance.h"
#include "effects/effect.h"
#include "cardDefinition.h"

#include "effects/gainArmorEffect.h"

#include <memory>

CardFactory::CardFactory()
{
    registerCards();
}

CardFactory::~CardFactory() {}

void CardFactory::registerDefinition(std::string_view cardId, std::unique_ptr<CardDefinition> uniqueCardDefinition)
{
    auto [it, inserted] = m_cardMap.emplace(std::string(cardId), std::move(uniqueCardDefinition));

    if (!inserted)
    {
        DEBUG_LOG("CardDefinition for " << cardId << " is already present in the map.");
        return;
    }

    DEBUG_LOG("CardDefinition for " << cardId << " has been inserted in the map.");
}

void CardFactory::registerCards()
{
    std::vector<std::unique_ptr<Effect>> shieldWarriorEffects;
    shieldWarriorEffects.emplace_back(std::make_unique<GainArmorEffect>());
    registerDefinition("shieldWarrior", std::make_unique<CardDefinition>("shieldWarrior", "Shield Warrior", 2, 1, 1, std::move(shieldWarriorEffects)));
}

std::unique_ptr<Card> CardFactory::makeSingleCard(const std::string &cardId)
{
    std::unique_ptr<Card> card{std::make_unique<Card>(*m_cardMap.at(cardId))};
    DEBUG_LOG("Card " << cardId << " has been created ");
    return card;
}
