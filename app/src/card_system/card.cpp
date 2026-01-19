#include "card.h"
#include "cardDefinition.h"

Card::Card(const CardDefinition &definition) : m_definition{&definition},
                                               m_dmg{m_definition->get_base_dmg()},
                                               m_armor{m_definition->get_base_armor()},
                                               m_cost{m_definition->get_base_cost()}
{
}