#include "cardInstance.h"
#include "cardDefinition.h"

CardInstance::CardInstance(const CardDefinition& definition)
    : m_definition{&definition}, m_baseCardParams{m_definition->getCardParams()},
      m_cost{m_definition->getBaseCost()}
{
}

const CardDefinition& CardInstance::getCardDefinition() const { return *m_definition; }

const CardParams& CardInstance::getCardParams() const { return m_baseCardParams; }

void CardInstance::increaseArmor(int amount) { m_baseCardParams.armor += amount; }
void CardInstance::increaseDamage(int amount) { m_baseCardParams.damage += amount; }
void CardInstance::increaseActions(int amount) { m_baseCardParams.actions += amount; }
void CardInstance::increaseDrawing(int amount) { m_baseCardParams.drawing += amount; }

void CardInstance::decreaseArmor(int amount)
{
    m_baseCardParams.armor = std::max(0, m_baseCardParams.armor - amount);
}
void CardInstance::decreaseDamage(int amount)
{
    m_baseCardParams.damage = std::max(0, m_baseCardParams.damage - amount);
}
void CardInstance::decreaseActions(int amount)
{
    m_baseCardParams.actions = std::max(0, m_baseCardParams.actions - amount);
}
void CardInstance::decreaseDrawing(int amount)
{
    m_baseCardParams.drawing = std::max(0, m_baseCardParams.drawing - amount);
}

void CardInstance::applyModifiers(const CardParams& cardParams)
{
    increaseArmor(cardParams.armor);
    increaseDamage(cardParams.damage);
    increaseDrawing(cardParams.drawing);
    increaseActions(cardParams.actions);
}