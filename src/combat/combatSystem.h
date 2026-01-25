#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

#include "combatEvents.h"

class Entity;

class CombatSystem
{
  public:
    void gainArmor(Entity& target, int amount);
    DamageResult dealDamage(const DamageInfo& damageInfo);
    void heal(Entity& target, int amount);
    void resetArmor(Entity& target);
    bool isDead(const Entity& target);

  private:
};

#endif // COMBATSYSTEM_H