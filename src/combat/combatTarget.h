#ifndef COMBATTARGET_H
#define COMBATTARGET_H

#include <string_view>
#include <unordered_map>

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

namespace target
{
inline const std::unordered_map<std::string_view, Target> targetMap{{"self", Target::Self},
                                                                    {"opponent", Target::Opponent}};
} // namespace target
#endif // COMBATTARGET_H
