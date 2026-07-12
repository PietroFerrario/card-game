#ifndef ENEMYMOVE_H
#define ENEMYMOVE_H

#include "cards/cardParams.h"
#include "effects/effect.h"
#include <memory>
#include <string>
#include <vector>

/**
 * @brief Describes a single enemy action resolved during combat.
 *
 * EnemyMove groups an ordered list of effects with the numeric parameters
 * used during resolution.
 *
 * EnemyMove does not execute itself; it is selected by Enemy and resolved externally by the
 * CardMatch.
 */
struct EnemyMove
{

    /// @brief name of the move (used for logging/UI).
    std::string name;

    std::string description;

    /// @brief Numeric parameters supplied to effects during resolution.
    CardParams effectParams;

    /// @brief Ordered list of effects executed when this move is resolved.
    std::vector<std::unique_ptr<Effect>> effectList{};
};

#endif // ENEMYMOVE_H
