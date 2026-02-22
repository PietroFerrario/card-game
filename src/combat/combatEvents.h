#ifndef COMBATEVENTS_H
#define COMBATEVENTS_H

class Entity;

enum class DamageResolution
{
    HitArmorFirst,
    IgnoreArmor,
};

struct DamageInfo
{
    // Entity* attacker;
    Entity& target;
    int amount;
    // DamageResolution damageResolution = DamageResolution::HitArmorFirst;
    bool ignoreArmor{false};
};

struct DamageResult
{
    int requested;
    int blocked;
    int hpDamage;
    bool targetDied;
};

#endif // COMBATEVENTS_H