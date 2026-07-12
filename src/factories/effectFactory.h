#ifndef EFFECTFACTORY_H
#define EFFECTFACTORY_H

#include "effects/effect.h"

#include "combat/combatTarget.h"
#include "effects/effectName.h"
#include <any>
#include <memory>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>

class EffectFactory
{
  public:
    EffectFactory();

    std::vector<std::unique_ptr<Effect>>
    makeEffectList(const std::vector<std::pair<EffectName, Target>>& effectDataList);

  private:
    std::unordered_map<EffectName, std::unique_ptr<Effect> (*)(Target)> m_effectMap;

    static std::unique_ptr<Effect> makeGainArmorEffect(Target target);
    static std::unique_ptr<Effect> makeGainAttackEffect(Target target);
    static std::unique_ptr<Effect> makeGainActionsEffect(Target target);
    static std::unique_ptr<Effect> makeDrawCardsEffect(Target target);

    // Enemies effect
    static std::unique_ptr<Effect> makeLimitCardToPlayEffect(Target target);
    static std::unique_ptr<Effect> makeTakeHostageEffect(Target target);
};

#endif // EFFECTFACTORY_H
