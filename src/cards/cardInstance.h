#ifndef CARDINSTANCE_H
#define CARDINSTANCE_H

#include "cards/cardParams.h"

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
    int getDamage() const { return m_baseCardParams.damage; }
    /// @brief Returns the card's current armor value.
    int getArmor() const { return m_baseCardParams.armor; }

    void increaseArmor(int amount);
    void increaseDamage(int amount);
    void increaseActions(int amount);
    void increaseDrawing(int amount);

    void decreaseArmor(int amount);
    void decreaseDamage(int amount);
    void decreaseActions(int amount);
    void decreaseDrawing(int amount);

    void increaseTemporaryArmor(int amount);
    void increaseTemporaryDamage(int amount);
    void increaseTemporaryActions(int amount);
    void increaseTemporaryDrawing(int amount);

    void multiplyArmor(int multiplier);
    void multiplyDamage(int multiplier);
    void multiplyActions(int multiplier);
    void multiplyDrawing(int multiplier);

    void applyModifiers(const CardParams& cardParams);
    void applyMultiplier(const CardParams& cardParams);
    void applyTemporaryModifiers(const CardParams& cardParams);

    void resetTemporaryModifiers();
    void applyTemporaryBuff(const CardParams& cardParams);

    /**
     * @brief Returns the immutable definition this instance was created from.
     *
     * Used for name, ID, effect list, and base values.
     */
    const CardDefinition& getCardDefinition() const;

    CardParams getTotalCardParams() const;

  private:
    const CardDefinition* m_definition; ///< Non-owning pointer to shared static definition.

    CardParams m_baseCardParams{}; ///< Base card parameters values (static during combat).
    CardParams m_temporaryModifiersParams{}; ///< Modifiers applied during combat.

    int m_cost{}; ///< Runtime cost (modifiable during combat).
};

#endif // CARDINSTANCE_H