#ifndef CARD_H
#define CARD_H

class CardDefinition;

class Card
{
public:
    Card(const CardDefinition &definition);

    int getDamage() const { return m_damage; }
    int getArmor() const { return m_armor; }

private:
    const CardDefinition *m_definition;

    int m_damage{};
    int m_armor{};
    int m_cost{};
};

#endif // CARD_H