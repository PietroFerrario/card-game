#include "cardDefinition.h"
#include "effects/effect.h"

#include <utility>

CardDefinition::CardDefinition(std::string_view cardId, std::string_view cardName,
                               std::string_view cardDescription, const CardParams& cardParams,
                               std::vector<std::unique_ptr<Effect>> effectList, int baseCost)
    : m_cardId{cardId}, m_cardName{cardName}, m_cardDescription{cardDescription},
      m_cardParams{cardParams}, m_baseCost{baseCost}, m_effectList{std::move(effectList)}
{
}

CardDefinition::~CardDefinition() = default;