#ifndef CARDSLOADER_H
#define CARDSLOADER_H

#include "cards/cardTag.h"
#include "combat/combatTarget.h"
#include "effectFactory.h"
#include "effects/effectName.h"

#include <memory>
#include <nlohmann/json.hpp>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class CardsLoader
{
  public:
    CardsLoader();

    std::vector<std::unique_ptr<CardDefinition>> parseCardsList();

  private:
    std::vector<std::pair<EffectName, Target>>
    makeEffectDataList(const nlohmann::json& jsonEffectList);

    nlohmann::json m_data{};
    EffectFactory m_effectFactory;

    std::unique_ptr<CardDefinition> loadCard(const nlohmann::json& card);
    std::unordered_set<CardTag> makeCardTagSet(const nlohmann::json& cardTagData);

    inline static const std::unordered_map<std::string_view, CardTag> m_cardTagMap{
        {"ranged", CardTag::Ranged}, {"melee", CardTag::Melee}, {"wiht", CardTag::Wiht},
        {"beast", CardTag::Beast},   {"clog", CardTag::Clog},   {"common", CardTag::Common},
        {"unique", CardTag::Unique}};
};

#endif // CARDSLOADER_H
