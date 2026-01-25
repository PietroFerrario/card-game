#ifndef COMBATEVENTS_H
#define COMBATEVENTS_H

class Entity;

enum class DamageResolution
{
    Attack,
    IgnoreArmor,
};

struct DamageInfo
{
    Entity* attacker;
    Entity* target;
    int amount;
    DamageResolution damageResolution = DamageResolution::Attack;
};

struct DamageResult
{
    int requested;
    int blocked;
    int hpDamage;
    bool targetDied;
};

#endif // COMBATEVENTS_H