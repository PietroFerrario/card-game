#ifndef CARD_H
#define CARD_H

class CardDefinition;

class Card
{
public:
    Card(const CardDefinition &definition);

    int get_dmg() const { return m_dmg; }
    int get_def() const { return m_armor; }

private:
    const CardDefinition *m_definition;

    int m_dmg{};
    int m_armor{};
    int m_cost{};
};

#endif // CARD_H