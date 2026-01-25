#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <string_view>

class Entity
{
  public:
    Entity() {}
    Entity(int hp) : m_hp{hp} {}

    std::string_view getName() const { return m_name; }

    int getArmor() const { return m_armor; }
    void resetArmor() { m_armor = 0; }
    void increaseArmor(int amount) { m_armor += amount; }
    void lowerArmor(int amount)
    {
        m_armor -= amount;
        if (m_armor <= 0)
            m_armor = 0;
    }

    int getHp() const { return m_hp; }
    void lowerHp(int amount) { m_hp -= amount; }
    void increaseHp(int amount) { m_hp += amount; }

  protected:
    int m_hp{};
    int m_armor{};
    std::string m_name{};
};

#endif // ENTITY_H