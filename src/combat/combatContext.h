#ifndef COMBATCONTEXT_H
#define COMBATCONTEXT_H

#include "combatTarget.h"

class CombatSystem;
class Entity;

class CombatContext
{
  public:
    CombatContext(CombatSystem& combatSystem, Entity& actor, Entity& opponent)
        : m_combatSystem{combatSystem}, m_actor{actor}, m_opponent{opponent}
    {
    }

    void gainArmor(Target target, int amount);

  private:
    CombatSystem& m_combatSystem;
    Entity& m_actor;
    Entity& m_opponent;

    Entity& resolveTarget(Target target);
};

#endif // COMBATCONTEXT_H