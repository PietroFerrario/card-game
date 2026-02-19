#ifndef COMBATCONTEXT_H
#define COMBATCONTEXT_H

#include "combatTarget.h"

class CombatSystem;
class Entity;

/**
 * @brief Execution context for resolving combat effects.
 *
 * CombatContext binds an actor/opponent relationship for the current action and
 * provides a narrow set of combat operations that effects may invoke.
 *
 * Effects target using logical selectors (Target::Self / Target::Opponent).
 * CombatContext resolves these selectors to Entity references and forwards
 * requests to CombatSystem, which owns the combat rules.
 *
 * CombatContext does not own any objects; it stores references that must outlive it.
 */
class CombatContext
{
  public:
    /**
     * @brief Constructs a context for effect resolution.
     *
     * @param combatSystem Combat rules engine used to apply mutations.
     * @param actor Entity performing the current action (Target::Self).
     * @param opponent Entity opposing the actor (Target::Opponent).
     */
    CombatContext(CombatSystem& combatSystem, Entity& actor, Entity& opponent)
        : m_combatSystem{combatSystem}, m_actor{actor}, m_opponent{opponent}
    {
    }

    /**
     * @brief Grants armor to the selected logical target.
     *
     * Resolves the target (self/opponent) and forwards the operation to CombatSystem.
     *
     * @param target Logical target selector.
     * @param amount Armor amount to add.
     */
    void gainArmor(Target target, int amount);

  private:
    CombatSystem& m_combatSystem;
    Entity& m_actor;
    Entity& m_opponent;

    /**
     * @brief Resolves a logical Target to the corresponding Entity in this context.
     *
     * @param target Logical target selector.
     * @return Reference to the resolved Entity (actor or opponent).
     */
    Entity& resolveTarget(Target target);
};

#endif // COMBATCONTEXT_H