#ifndef CARDINSTANCE_H
#define CARDINSTANCE_H

#include "effects/effectParams.h"

#include <string_view>

class CardDefinition;

/**
 * @brief Represents a runtime instance of a card during combat.
 *
 * CardInstance holds temporary state used in a single combat:
 * - Current damage, armor, and cost values (copied from CardDefinition)
 * - A reference to the immutable CardDefinition it was created from
 *
 * Used for tracking temporary buffs, debuffs, or cost changes.
 * CardInstances are created at combat start and destroyed at combat end.
 */
class CardInstance
{
  public:
    /**
     * @brief Constructs a CardInstance from a CardDefinition.
     *
     * Copies base values (damage, armor, cost) from the definition.
     *
     * @param definition Immutable reference to the source CardDefinition.
     */
    CardInstance(const CardDefinition& definition);

    /// @brief Returns the card's current damage value.
    int getDamage() const { return m_damage; }
    /// @brief Returns the card's current armor value.
    int getArmor() const { return m_armor; }

    /**
     * @brief Returns the immutable definition this instance was created from.
     *
     * Used for name, ID, effect list, and base values.
     */
    const CardDefinition& getCardDefinition() const;

    EffectParams getEffectParams() const;

  private:
    const CardDefinition* m_definition; ///< Non-owning pointer to shared static definition.

    int m_damage{}; ///< Runtime damage value (modifiable during combat)
    int m_armor{};  ///< Runtime armor value (modifiable during combat).
    int m_cost{};   ///< Runtime cost (modifiable during combat).
};

#endif // CARDINSTANCE_H