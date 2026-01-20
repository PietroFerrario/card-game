#ifndef CARDINSTANCE_H
#define CARDINSTANCE_H

class CardDefinition;

class CardInstance
{
public:
    CardInstance(const CardDefinition &definition);

    int getDamage() const { return m_damage; }
    int getArmor() const { return m_armor; }

private:
    const CardDefinition *m_definition;

    int m_damage{};
    int m_armor{};
    int m_cost{};
};

#endif // CARDINSTANCE_H