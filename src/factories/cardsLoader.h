#ifndef CARDSLOADER_H
#define CARDSLOADER_H

#include "effectFactory.h"
#include <memory>
#include <nlohmann/json.hpp>
#include <vector>

class CardsLoader
{
  public:
    CardsLoader();

    std::vector<std::unique_ptr<CardDefinition>> parseCardsList();

  private:
    nlohmann::json m_data{};
    EffectFactory m_effectFactory;

    std::unique_ptr<CardDefinition> loadCard(const nlohmann::json& card);
};

#endif // CARDSLOADER_H