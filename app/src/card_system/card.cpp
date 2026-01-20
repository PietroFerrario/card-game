#include "card.h"
#include "cardDefinition.h"

Card::Card(const CardDefinition &definition) : m_definition{&definition},
                                               m_damage{m_definition->getBaseDamage()},
                                               m_armor{m_definition->getBaseArmor()},
                                               m_cost{m_definition->getBaseCost()}
{
}