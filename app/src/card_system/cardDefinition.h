#ifndef CARDDEFINITION_H
#define CARDDEFINITION_H

#include <string>
#include <string_view>
#include <vector>
#include <memory>

class Effect;

class CardDefinition
{

public:
    CardDefinition::CardDefinition(std::string_view card_id, std::string_view card_name,
                                   int base_dmg = 0, int base_armor = 0, int base_cost = 1,
                                   std::vector<std::unique_ptr<Effect>> effect_list = {});

    std::string_view get_name() const { return m_card_name; }

    int get_base_dmg() const { return m_base_dmg; }
    int get_base_armor() const { return m_base_armor; }
    int get_base_cost() const { return m_base_cost; }

    ~CardDefinition();

private:
    std::string m_card_id{};
    std::string m_card_name{};

    int m_base_dmg{0};
    int m_base_armor{0};
    int m_base_cost{1};

    std::vector<std::unique_ptr<Effect>> m_effect_list{};
};

#endif // CARDDEFINITION_H