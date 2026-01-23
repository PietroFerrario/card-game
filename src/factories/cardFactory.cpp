#include "cardFactory.h"
#include "cards/cardDefinition.h"
#include "cards/cardInstance.h"
#include "cards/effect.h"
#include "util/debug.h"

#include "cards/effects/gainArmorEffect.h"

#include <memory>
/**
 * @brief Construct a new Card Factory:: Card Factory object
 *
 */
CardFactory::CardFactory() { registerCards(); }

CardFactory::~CardFactory() {}

void CardFactory::registerDefinition(std::string_view cardId,
                                     std::unique_ptr<CardDefinition> uniqueCardDefinition)
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
    registerDefinition("shieldWarrior",
                       std::make_unique<CardDefinition>("shieldWarrior", "Shield Warrior", 2, 1, 1,
                                                        std::move(shieldWarriorEffects)));
}

std::unique_ptr<CardInstance> CardFactory::makeSingleCard(const std::string& cardId) const
{
    std::unique_ptr<CardInstance> card{std::make_unique<CardInstance>(*m_cardMap.at(cardId))};
    DEBUG_LOG("CardInstance of " << cardId << " has been created.");
    return card;
}
