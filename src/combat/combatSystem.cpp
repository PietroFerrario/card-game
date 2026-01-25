#include "combatSystem.h"
#include "entities/entity.h"
#include "util/debug.h"

void CombatSystem::gainArmor(Entity& target, int amount)
{
    target.increaseArmor(amount);
    DEBUG_LOG("Increasing Armor of " << target.getName() << ": +" << amount);
}
void CombatSystem::resetArmor(Entity& target) { target.resetArmor(); }

void CombatSystem::heal(Entity& target, int amount) { target.increaseHp(amount); }

DamageResult CombatSystem::dealDamage(const DamageInfo& info)
{
    DamageResult result{0, 0, 0, false};

    if (!info.target)
    {
        return result;
    }

    const int amount = std::max(0, info.amount);
    result.requested = amount;

    if (info.damageResolution == DamageResolution::IgnoreArmor)
    {
        info.target->lowerHp(amount);
        result.hpDamage = amount;
    }
    else
    {
        const int armor = info.target->getArmor();
        const int blocked = std::min(amount, armor);
        const int hpDamage = amount - blocked;

        if (blocked > 0)
            info.target->lowerArmor(blocked);
        if (hpDamage > 0)
        {
            info.target->lowerHp(hpDamage);
        }
        result.blocked = blocked;
        result.hpDamage = hpDamage;
    }
    result.targetDied = isDead(*info.target);
    return result;
}

bool CombatSystem::isDead(const Entity& target) { return target.getHp() <= 0; }
