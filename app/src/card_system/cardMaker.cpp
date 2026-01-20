#include "cardMaker.h"
#include "util/debug.h"
#include "card.h"
#include "effects/effect.h"
#include "cardDefinition.h"

#include "effects/gainArmorEffect.h"

#include <memory>

CardMaker::CardMaker()
{
    registerCards();
}

void CardMaker::registerDefinition(std::string_view cardId, std::unique_ptr<CardDefinition> uniqueCardDefinition)
{
    auto [it, inserted] = m_cardMap.emplace(std::string(cardId), std::move(uniqueCardDefinition));

    if (!inserted)
    {
        DEBUG_LOG("CardDefinition for " << cardId << " is already present in the map.");
        return;
    }

    DEBUG_LOG("CardDefinition for " << cardId << " has been inserted in the map.");
}

void CardMaker::registerCards()
{
    std::vector<std::unique_ptr<Effect>> shieldWarriorEffects;
    shieldWarriorEffects.emplace_back(std::make_unique<GainArmorEffect>());
    registerDefinition("shieldWarrior", std::make_unique<CardDefinition>("shieldWarrior", "Shield Warrior", 2, 1, 1, std::move(shieldWarriorEffects)));
}

Card CardMaker::makeSingleCard(const std::string &cardId)
{
    Card card{*m_cardMap.at(cardId)};
    DEBUG_LOG("Card " << cardId << " has been created ");
    return card;
}