#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <string_view>

/**
 * @brief Base class representing a combat-capable entity.
 *
 * Entity stores core combat state such as HP, armor, and attack value.
 * It provides low-level mutation primitives but does not implement
 * combat rules or gameplay logic.
 *
 * Higher-level systems (e.g., CombatSystem) are responsible for enforcing
 * rules and constraints when mutating entity state.
 */
class Entity
{
  public:
    Entity() {}
    Entity(int hp, int attack = 0, int armor = 0) : m_hp{hp}, m_attack{attack}, m_armor{armor} {}

    /// @brief Returns the display name of the entity.
    std::string_view getName() const { return m_name; }

    /// @brief Returns the current armor value.
    int getArmor() const { return m_armor; }

    /// @brief Returns the current attack value.
    int getAttack() const { return m_attack; }

    /// @brief Resets armor to zero.
    void resetArmor() { m_armor = 0; }

    /// @brief Resets attack to zero.
    void resetAttack() { m_attack = 0; }

    /// @brief Increases armor by the given amount.
    void increaseArmor(int amount) { m_armor += amount; }

    /// @brief Increases attack by the given amount.
    void increaseAttack(int amount) { m_attack += amount; }

    /**
     * @brief Decreases armor by the given amount.
     *
     * Armor is clamped to zero if the reduction would make it negative.
     */
    void lowerArmor(int amount)
    {
        m_armor -= amount;
        if (m_armor <= 0)
            m_armor = 0;
    }

    /// @brief Returns the current HP value.
    int getHp() const { return m_hp; }

    /// @brief Decreases HP by the given amount.
    void lowerHp(int amount) { m_hp -= amount; }

    /// @brief Increases HP by the given amount.
    void increaseHp(int amount) { m_hp += amount; }

  protected:
    int m_hp{};
    int m_armor{};
    int m_attack{};
    std::string m_name{};
};

#endif // ENTITY_H