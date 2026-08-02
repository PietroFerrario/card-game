#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

#include "combatEvents.h"

class Entity;

/**
 * @brief Central authority for combat rules and state mutation.
 *
 * CombatSystem implements all rule-driven combat operations such as damage,
 * armor handling, healing, and death checks.
 *
 * Gameplay logic (effects, match orchestration) must not mutate Entity state directly.
 * All combat-related mutations should be performed through this class.
 */
class CombatSystem
{
  public:
    /**
     * @brief Grants armor to the target entity.
     *
     * @param target Entity receiving the armor.
     * @param amount Armor amount to add.
     */
    void gainArmor(Entity& target, int amount);

    /**
     * @brief Grants attack to the target entity.
     *
     * @param target Entity receiving the armor.
     * @param amount Attack amount to add.
     */
    void gainAttack(Entity& target, int amount);

    void endTurnReset(Entity& entity, bool maintainArmour);

    /**
     * @brief Resolves damage against a target according to combat rules.
     *
     * Applies armor interaction based on the specified damage resolution mode
     * and returns a detailed result describing the outcome.
     *
     * @param damageInfo Damage request (amount, target, resolution mode).
     * @return DamageResult describing blocked damage, HP damage, and death state.
     */
    DamageResult dealDamage(Entity& target, int amount, bool ignoreArmor = false);

    /**
     * @brief Heals the target entity by the specified amount.
     *
     * @param target Entity to heal.
     * @param amount HP amount to restore.
     */
    void heal(Entity& target, int amount);

    /**
     * @brief Resets the target entity's armor to zero.
     *
     * @param target Entity whose armor is reset.
     */
    void resetArmor(Entity& target);

    /**
     * @brief Checks whether the target entity is dead.
     *
     * @param target Entity to check.
     * @return true if the entity's HP is zero or below.
     */
    bool isDead(const Entity& target);

  private:
};

#endif // COMBATSYSTEM_H
