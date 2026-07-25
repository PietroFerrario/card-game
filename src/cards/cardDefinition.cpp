#include "cardDefinition.h"
#include "effects/effect.h"

#include <utility>

CardDefinition::CardDefinition(std::string_view cardId, std::string_view cardName,
                               std::string_view cardDescription,
                               std::unordered_set<CardTag> cardTagSet,
                               CardDisposalMode cardDisposalMode, const CardParams& cardParams,
                               std::vector<std::unique_ptr<Effect>> effectList, int baseCost)
    : m_cardId{cardId}, m_cardName{cardName}, m_cardDescription{cardDescription},
      m_cardTagSet{std::move(cardTagSet)}, m_cardDisposalMode{cardDisposalMode},
      m_cardParams{cardParams}, m_baseCost{baseCost}, m_effectList{std::move(effectList)}
{
}

CardDefinition::~CardDefinition() = default;

bool CardDefinition::hasTag(CardTag cardTag) const { return m_cardTagSet.contains(cardTag); }
