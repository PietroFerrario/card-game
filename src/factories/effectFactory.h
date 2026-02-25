#ifndef EFFECTFACTORY_H
#define EFFECTFACTORY_H

#include "effects/effect.h"

#include <any>
#include <memory>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>

enum class Target;

class EffectFactory
{
  public:
    EffectFactory();

    std::vector<std::unique_ptr<Effect>> makeEffectList(const nlohmann::json& effectList);

  private:
    std::unordered_map<std::string, std::unique_ptr<Effect> (*)(const nlohmann::json& effect)>
        m_effectMap;

    static Target identifyTarget(const std::string& targetSpecifier);

    static std::unique_ptr<Effect> makeGainArmorEffect(const nlohmann::json& effect);
    static std::unique_ptr<Effect> makeGainAttackEffect(const nlohmann::json& effect);
    static std::unique_ptr<Effect> makeGainActionsEffect(const nlohmann::json& effect);
    static std::unique_ptr<Effect> makeDrawCardsEffect(const nlohmann::json& effect);
};

#endif // EFFECTFACTORY_H