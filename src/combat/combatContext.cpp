#include "combatContext.h"
#include "combat/combatEvents.h"
#include "combatSystem.h"
#include "entities/entity.h"
#include "util/debug.h"

#include <utility>

CombatContext::CombatContext(CombatSystem& combatSystem, Entity& actor, Entity& opponent,
                             std::vector<std::string>* effectMessage)
    : m_combatSystem{combatSystem}, m_actor{actor}, m_opponent{opponent},
      m_effectMessage{effectMessage}
{
}

Entity& CombatContext::resolveTarget(Target target)
{
    switch (target)
    {
    case Target::Self:
    {
        // DEBUG_LOG("Selected Self");
        return m_actor;
    }
    case Target::Opponent:
    {
        // DEBUG_LOG("Selected Opponent");
        return m_opponent;
    }
    default:
    {
        DEBUG_LOG("No valid target selected. Crashing");
        std::unreachable();
    }
    }
    std::unreachable();
}

const Entity& CombatContext::resolveTarget(Target target) const
{
    switch (target)
    {
    case Target::Self:
    {
        // DEBUG_LOG("Selected Self");
        return m_actor;
    }
    case Target::Opponent:
    {
        // DEBUG_LOG("Selected Opponent");
        return m_opponent;
    }
    default:
    {
        DEBUG_LOG("No valid target selected. Crashing");
        std::unreachable();
    }
    }
    std::unreachable();
}

std::string CombatContext::messageTarget(Target target) const
{

    if (target != Target::Self)
    {
        return std::string(resolveTarget(target).getName()) + " ";
    }
    else
        return "";
}

void CombatContext::gainArmor(Target target, int amount)
{
    m_combatSystem.gainArmor(resolveTarget(target), amount);
    if (m_effectMessage)
    {
        m_effectMessage->emplace_back(std::format("{}Armor: +{}", messageTarget(target), amount));
    }
}

void CombatContext::gainAttack(Target target, int amount)
{
    m_combatSystem.gainAttack(resolveTarget(target), amount);
    if (m_effectMessage)
    {
        m_effectMessage->emplace_back(std::format("{}Attack: +{}", messageTarget(target), amount));
    }
}

DamageResult CombatContext::dealDamage(Target target, int amount, bool ignoreArmor)
{
    return m_combatSystem.dealDamage(resolveTarget(target), amount, ignoreArmor);
}
