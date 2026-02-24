#include "cardInstance.h"
#include "cardDefinition.h"

CardInstance::CardInstance(const CardDefinition& definition)
    : m_definition{&definition}, m_cardParams{m_definition->getCardParams()},
      m_cost{m_definition->getBaseCost()}
{
}

const CardDefinition& CardInstance::getCardDefinition() const { return *m_definition; }

const CardParams& CardInstance::getCardParams() const { return m_cardParams; }