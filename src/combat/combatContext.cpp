#include "combatContext.h"
#include "combat/combatEvents.h"
#include "combatSystem.h"
#include "util/debug.h"

#include <utility>

Entity& CombatContext::resolveTarget(Target target)
{
    switch (target)
    {
    case Target::Self:
    {
        DEBUG_LOG("Selected Self");
        return m_actor;
    }
    case Target::Opponent:
    {
        DEBUG_LOG("Selected Opponent");
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

void CombatContext::gainArmor(Target target, int amount)
{
    m_combatSystem.gainArmor(resolveTarget(target), amount);
}

void CombatContext::gainAttack(Target target, int amount)
{
    m_combatSystem.gainAttack(resolveTarget(target), amount);
}

DamageResult CombatContext::dealDamage(Target target, int amount, bool ignoreArmor = false)
{
    return m_combatSystem.dealDamage(resolveTarget(target), amount, ignoreArmor);
}
