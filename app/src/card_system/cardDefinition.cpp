#include "cardDefinition.h"
#include "effects/effect.h"

#include <utility>

CardDefinition::CardDefinition(std::string_view cardId, std::string_view cardName,
                               int baseDamage, int baseArmor, int baseCost,
                               std::vector<std::unique_ptr<Effect>> effectList) : m_cardId{cardId},
                                                                                  m_cardName{cardName},
                                                                                  m_baseDamage{baseDamage},
                                                                                  m_baseArmor{baseArmor},
                                                                                  m_baseCost{baseCost},
                                                                                  m_effectList{std::move(effectList)}
{
}

CardDefinition::~CardDefinition() = default;