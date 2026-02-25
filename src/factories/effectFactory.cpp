#include "effectFactory.h"
#include "combat/combatTarget.h"
#include "effects/drawCardsEffect.h"
#include "effects/gainActionsEffect.h"
#include "effects/gainArmorEffect.h"
#include "effects/gainAttackEffect.h"
#include "util/debug.h"
#include <cassert>

EffectFactory::EffectFactory()
{
    m_effectMap["gainArmor"] = makeGainArmorEffect;
    m_effectMap["gainAttack"] = makeGainAttackEffect;
    m_effectMap["drawCards"] = makeDrawCardsEffect;
    m_effectMap["gainActions"] = makeGainActionsEffect;
}

std::vector<std::unique_ptr<Effect>>
EffectFactory::makeEffectList(const nlohmann::json& dataEffectList)
{
    std::vector<std::unique_ptr<Effect>> effectList;

    for (const auto& dataEffect : dataEffectList)
    {
        auto mapIter = m_effectMap.find(dataEffect.at("effect").get_ref<const std::string&>());

        if (mapIter == m_effectMap.end())
        {
            assert(false && "Unknown effect specifier");
            std::terminate();
        }

        effectList.emplace_back(std::move(mapIter->second(dataEffect)));
    }

    return effectList;
}

std::unique_ptr<Effect> EffectFactory::makeGainArmorEffect(const nlohmann::json& effect)
{
    return std::make_unique<GainArmorEffect>(
        identifyTarget(effect.at("target").get_ref<const std::string&>()));
}

std::unique_ptr<Effect> EffectFactory::makeGainAttackEffect(const nlohmann::json& effect)
{
    return std::make_unique<GainAttackEffect>(
        identifyTarget(effect.at("target").get_ref<const std::string&>()));
}

std::unique_ptr<Effect> EffectFactory::makeGainActionsEffect(const nlohmann::json& effect)
{
    return std::make_unique<GainActionsEffect>();
}

std::unique_ptr<Effect> EffectFactory::makeDrawCardsEffect(const nlohmann::json& effect)
{
    return std::make_unique<DrawCardsEffect>();
}

Target EffectFactory::identifyTarget(const std::string& targetSpecifier)
{
    if (targetSpecifier == "self")
    {
        return Target::Self;
    }
    if (targetSpecifier == "opponent")
    {
        return Target::Opponent;
    }

    assert(false && "Unknown target specifier");
    std::terminate();
}