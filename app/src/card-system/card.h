#ifndef CARD_H
#define CARD_H

#include <string>
#include <string_view>

class Card
{
public:
    std::string_view get_name() const { return m_card_name; }
    std::string_view get_effect() const { return m_card_effect; }
    std::string_view get_effect_short() const { return m_card_effect_short; }

    int get_dmg() const { return m_dmg; }

private:
    std::string m_card_name{};
    std::string m_card_effect{};
    std::string m_card_effect_short{};
    int m_dmg{};
};

#endif // CARD_H