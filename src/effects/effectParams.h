#ifndef EFFECTPARAMS_H
#define EFFECTPARAMS_H

/**
 * @brief Numeric parameters used to resolve gameplay effects.
 *
 * EffectParams provides the numeric values consumed by Effect implementations
 * during resolution (e.g., damage, armor).
 *
 * The same parameter structure is used for both card effects and enemy moves,
 * allowing Effect behavior to remain stateless and reusable.
 */
struct EffectParams
{
    int damage;
    int armor;
};

#endif // EFFECTPARAMS_H