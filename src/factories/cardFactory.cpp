#include "cardFactory.h"
#include "cards/cardDefinition.h"
#include "cards/cardInstance.h"
#include "cards/cardParams.h"
#include "combat/combatTarget.h"
#include "effects/drawCardsEffect.h"
#include "effects/effect.h"
#include "effects/gainActionsEffect.h"
#include "effects/gainArmorEffect.h"
#include "effects/gainAttackEffect.h"
#include "util/debug.h"

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
    // NOTE: Cards are loaded into a temporary vector and then moved into the factory map.
    // This is intentional for now. Can be refactored later to a streaming "push" load
    // if memory or load-time ever become a problem.

    std::vector<std::unique_ptr<CardDefinition>> cardsDefinitionList{
        m_cardsLoader.parseCardsList()};

    for (auto& cardDefinition : cardsDefinitionList)
    {
        auto ID{cardDefinition->getID()};
        registerDefinition(ID, std::move(cardDefinition));
    }

    // std::vector<std::unique_ptr<Effect>> shieldWarriorEffects;
    // shieldWarriorEffects.emplace_back(std::make_unique<GainArmorEffect>(Target::Self));
    // shieldWarriorEffects.emplace_back(std::make_unique<GainAttackEffect>(Target::Self));
    // shieldWarriorEffects.emplace_back(std::make_unique<DrawCardsEffect>());
    // shieldWarriorEffects.emplace_back(std::make_unique<GainActionsEffect>());
    // registerDefinition("shieldWarrior",
    //                    std::make_unique<CardDefinition>(
    //                        "shieldWarrior", "Shield Warrior",
    //                        "Strong warrior with axe and round shield",
    //                        CardParams{.damage = 2, .armor = 1, .actions = 1, .drawing = 1},
    //                        std::move(shieldWarriorEffects)));
}

std::unique_ptr<CardInstance> CardFactory::makeSingleCard(const DeckEntry& deckEntry) const
{
    DEBUG_LOG("Card instance being created: " << m_cardMap.at(deckEntry.cardId));
    std::unique_ptr<CardInstance> card{
        std::make_unique<CardInstance>(*m_cardMap.at(deckEntry.cardId))};
    DEBUG_LOG("CardInstance of " << deckEntry.cardId << " has been created.");

    card->applyModifiers(deckEntry.permanentModifiers);

    return card;
}
