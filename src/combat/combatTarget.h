#ifndef COMBATTARGET_H
#define COMBATTARGET_H

/**
 * @brief Logical target selector used during effect resolution.
 *
 * Target represents an abstract combat target relative to the current action:
 * - Self refers to the entity performing the action.
 * - Opponent refers to the opposing entity.
 *
 * Logical targets are resolved to concrete entities by CombatContext.
 */
enum class Target
{
    Self,
    Opponent
};

#endif // COMBATTARGET_H