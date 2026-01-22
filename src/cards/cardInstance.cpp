#include "cardInstance.h"
#include "cardDefinition.h"

CardInstance::CardInstance(const CardDefinition& definition)
    : m_definition{&definition}, m_damage{m_definition->getBaseDamage()},
      m_armor{m_definition->getBaseArmor()}, m_cost{m_definition->getBaseCost()}
{
}

const CardDefinition& CardInstance::getCardDefinition() const { return *m_definition; }