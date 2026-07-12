#ifndef CARDSLOADER_H
#define CARDSLOADER_H

#include "combat/combatTarget.h"
#include "effectFactory.h"
#include "effects/effectName.h"

#include <memory>
#include <nlohmann/json.hpp>
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
};

#endif // CARDSLOADER_H
