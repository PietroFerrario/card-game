#include "cardDefinition.h"
#include "effects/effect.h"

#include <utility>

CardDefinition::CardDefinition(std::string_view card_id, std::string_view card_name,
                               int base_dmg, int base_armor, int base_cost,
                               std::vector<std::unique_ptr<Effect>> effect_list) : m_card_id{card_id},
                                                                                   m_card_name{card_name},
                                                                                   m_base_dmg{base_dmg},
                                                                                   m_base_armor{base_armor},
                                                                                   m_base_cost{base_cost},
                                                                                   m_effect_list{std::move(effect_list)}
{
}

CardDefinition::~CardDefinition() = default;