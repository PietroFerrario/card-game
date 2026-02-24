#ifndef CARDPARAMS_H
#define CARDPARAMS_H

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
    int damage{0};
    int armor{0};
    int actions{0};
    int drawing{0};
};

#endif // CARDPARAMS_H