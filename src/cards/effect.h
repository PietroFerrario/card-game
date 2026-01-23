#ifndef EFFECT_H
#define EFFECT_H

class CardMatch;
class CardInstance;

/**
 * @brief Abstract base class for all card effects.
 *
 * Effects define behavior that is executed when a card is played.
 * They do not store any numeric values or state — all values are read from the CardInstance.
 *
 * Effects request actions from CardMatch, but never modify entity state directly.
 *
 * All derived effects must implement the apply() method.
 */
class Effect
{
  public:
    /**
     * @brief Applies the effect during card resolution.
     *
     * @param card_match Reference to the combat authority managing the encounter.
     * @param card The card instance triggering this effect.
     */
    virtual void apply(CardMatch& card_match, CardInstance& card) = 0;

    /// @brief Virtual destructor.
    virtual ~Effect() = default;

  private:
};

#endif // EFFECT_H