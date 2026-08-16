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

    // Card effects
    static std::unique_ptr<Effect> makeBuffIfCardPlayedEffect(Target target);
    static std::unique_ptr<Effect> makeMaintainExcessArmorEffect(Target target);
    static std::unique_ptr<Effect> makeConvertExcessArmorIntoAttackEffect(Target target);
    static std::unique_ptr<Effect> makeAvoidDeathEffect(Target target);
    static std::unique_ptr<Effect> makeBuffOnPopulationEffect(Target target);

    // Enemies effects
    static std::unique_ptr<Effect> makeLimitCardToPlayEffect(Target target);
    static std::unique_ptr<Effect> makeTakeHostageEffect(Target target);
    static std::unique_ptr<Effect> makeAddClogCardToDeck(Target target);
    static std::unique_ptr<Effect> makeIncreaseDamaeEnemyMove(Target target);
};

#endif // EFFECTFACTORY_H
