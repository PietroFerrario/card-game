#include "cardInstance.h"
#include "cardDefinition.h"
#include "util/debug.h"

CardInstance::CardInstance(const CardDefinition& definition)
    : m_definition{&definition}, m_baseCardParams{m_definition->getCardParams()},
      m_cost{m_definition->getBaseCost()}
{
}

const CardDefinition& CardInstance::getCardDefinition() const { return *m_definition; }

CardParams CardInstance::getTotalCardParams() const
{
    return m_baseCardParams + m_temporaryModifiersParams;
}

void CardInstance::increaseArmor(int amount) { m_baseCardParams.armor += amount; }
void CardInstance::increaseDamage(int amount) { m_baseCardParams.damage += amount; }
void CardInstance::increaseActions(int amount) { m_baseCardParams.actions += amount; }
void CardInstance::increaseDrawing(int amount) { m_baseCardParams.drawing += amount; }

void CardInstance::increaseTemporaryArmor(int amount)
{
    m_temporaryModifiersParams.armor += amount;
}
void CardInstance::increaseTemporaryDamage(int amount)
{
    m_temporaryModifiersParams.damage += amount;
}
void CardInstance::increaseTemporaryActions(int amount)
{
    m_temporaryModifiersParams.actions += amount;
}
void CardInstance::increaseTemporaryDrawing(int amount)
{
    m_temporaryModifiersParams.drawing += amount;
}

void CardInstance::multiplyArmor(int multiplier)
{
    m_temporaryModifiersParams.armor +=
            m_baseCardParams.armor * multiplier - m_baseCardParams.armor;
}
void CardInstance::multiplyDamage(int multiplier)
{
    m_temporaryModifiersParams.damage +=
            m_baseCardParams.damage * multiplier - m_baseCardParams.damage;
}
void CardInstance::multiplyActions(int multiplier)
{
    m_temporaryModifiersParams.actions +=
            m_baseCardParams.actions * multiplier - m_baseCardParams.actions;
}
void CardInstance::multiplyDrawing(int multiplier)
{
    m_temporaryModifiersParams.drawing +=
            m_baseCardParams.drawing * multiplier - m_baseCardParams.drawing;
}

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

void CardInstance::applyTemporaryModifiers(const CardParams& cardParams)
{
    if (cardParams.upgradeCardParam.has_value() && cardParams.amount.has_value())
    {
        CardParams upgrade{upgradeCardParam::convertUpgradeCardParam(
                cardParams.amount.value(), cardParams.upgradeCardParam.value())};
        increaseTemporaryArmor(upgrade.armor);
        increaseTemporaryDamage(upgrade.damage);
        increaseTemporaryDrawing(upgrade.drawing);
        increaseTemporaryActions(upgrade.actions);
    }
}

void CardInstance::applyMultiplier(const CardParams& cardParams)
{
    if (cardParams.upgradeCardParam.has_value() && cardParams.multiplier.has_value())
    {
        switch (cardParams.upgradeCardParam.value())
        {
        case UpgradeCardParam::Attack:
            multiplyDamage(cardParams.multiplier.value());
            break;

        case UpgradeCardParam::Armor:
            multiplyArmor(cardParams.multiplier.value());
            break;

        case UpgradeCardParam::Action:
            multiplyActions(cardParams.multiplier.value());
            break;

        case UpgradeCardParam::Drawing:
            multiplyDrawing(cardParams.multiplier.value());
            break;

        default:
            DEBUG_LOG("End of ApplyMultiplier CardInstance side.");
        }
    }
}

void CardInstance::resetTemporaryModifiers()
{
    m_temporaryModifiersParams.armor = 0;
    m_temporaryModifiersParams.damage = 0;
    m_temporaryModifiersParams.actions = 0;
    m_temporaryModifiersParams.drawing = 0;
}

void CardInstance::applyTemporaryBuff(const CardParams& cardParams)
{
    applyTemporaryModifiers(cardParams);
    applyMultiplier(cardParams);
}