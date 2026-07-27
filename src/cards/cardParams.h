#ifndef CARDPARAMS_H
#define CARDPARAMS_H

#include <optional>
#include <string>

/**
 * @brief Numeric parameters used to resolve gameplay effects.
 *
 * CardParams provides the numeric values consumed by Effect implementations
 * during resolution (e.g., damage, armor).
 *
 * The same parameter structure is used for both card effects and enemy moves,
 * allowing Effect behavior to remain stateless and reusable.
 */
struct CardParams
{
    // Common one
    int damage{0};
    int armor{0};
    int actions{0};
    int drawing{0};

    // Enemy-based
    std::optional<int> amount;
    std::optional<std::string> referenceId;

    CardParams& operator+=(const CardParams& other)
    {
        damage += other.damage;
        armor += other.armor;
        actions += other.actions;
        drawing += other.drawing;
        return *this;
    }
};

#endif // CARDPARAMS_H
