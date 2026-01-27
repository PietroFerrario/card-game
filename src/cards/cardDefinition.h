#ifndef CARDDEFINITION_H
#define CARDDEFINITION_H

#include <memory>
#include <string>
#include <string_view>
#include <vector>

class Effect;

/**
 * @brief Immutable static data representing a card type.
 *
 * CardDefinition defines the core identity and behavior of a card:
 * - Unique ID and display name
 * - Base damage, armor, and cost values
 * - Ordered list of effects to apply when the card is played
 *
 * CardDefinitions are created once at startup and shared across all matches.
 * They do not contain any runtime state or combat logic.
 *
 * Effects are owned by the definition and used to build CardInstances at runtime.
 */
class CardDefinition
{

  public:
    /**
     * @brief Constructs a new CardDefinition with provided base values and effects.
     *
     * @param cardId Unique identifier for the card (used internally).
     * @param cardName Human-readable name for display purposes.
     * @param baseDamage Default damage value for the card.
     * @param baseArmor Default armor value for the card.
     * @param effectList Ordered list of effects applied when the card is played.
     * @param baseCost Default cost to play the card (1).
     */
    CardDefinition(std::string_view cardId, std::string_view cardName,
                   std::string_view cardDescription, int baseDamage = 0, int baseArmor = 0,
                   std::vector<std::unique_ptr<Effect>> effectList = {}, int baseCost = 1);

    /// @brief Returns the display name of the card.
    std::string_view getName() const { return m_cardName; }

    /// @brief Returns the internal ID of the card.
    std::string_view getID() const { return m_cardId; }

    std::string_view getDescription() const { return m_cardDescription; }

    /// @brief Returns the base damage value defined for the card.
    int getBaseDamage() const { return m_baseDamage; }
    /// @brief Returns the base armor value defined for the card.
    int getBaseArmor() const { return m_baseArmor; }
    /// @brief Returns the base energy cost to play the card.
    int getBaseCost() const { return m_baseCost; }

    /**
     * @brief Returns a const reference to the list of effects.
     *
     * Effects are applied in the order they appear in this list.
     * Each effect is owned by this definition and reused by all instances.
     */
    const std::vector<std::unique_ptr<Effect>>& getEffectList() const { return m_effectList; }

    /// @brief Destructor (default).
    ~CardDefinition();

  private:
    std::string m_cardId{};
    std::string m_cardName{};
    std::string m_cardDescription{};

    int m_baseDamage{0};
    int m_baseArmor{0};
    int m_baseCost{1};

    std::vector<std::unique_ptr<Effect>> m_effectList{};
};

#endif // CARDDEFINITION_H