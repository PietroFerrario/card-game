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
    CardDefinition(std::string_view cardId, std::string_view cardName,
                   int baseDamage = 0, int baseArmor = 0, int baseCost = 1,
                   std::vector<std::unique_ptr<Effect>> effectList = {});

    std::string_view getName() const { return m_cardName; }
    std::string_view getID() const { return m_cardId; }

    int getBaseDamage() const { return m_baseDamage; }
    int getBaseArmor() const { return m_baseArmor; }
    int getBaseCost() const { return m_baseCost; }

    ~CardDefinition();

private:
    std::string m_cardId{};
    std::string m_cardName{};

    int m_baseDamage{0};
    int m_baseArmor{0};
    int m_baseCost{1};

    std::vector<std::unique_ptr<Effect>> m_effectList{};
};

#endif // CARDDEFINITION_H