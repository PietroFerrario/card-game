#include "effectFactory.h"
#include "combat/combatTarget.h"
#include "effects/addClogCardToDeckEffect.h"
#include "effects/avoidDeathEffect.h"
#include "effects/buffIfCardPlayedEffect.h"
#include "effects/buffNextSpecifiedCardPlayedInTurnEffect.h"
#include "effects/buffOnPopulationEffect.h"
#include "effects/convertExcessArmorIntoAttackEffect.h"
#include "effects/drawCardsEffect.h"
#include "effects/gainActionsEffect.h"
#include "effects/gainArmorEffect.h"
#include "effects/gainAttackEffect.h"
#include "effects/hostageCardEffect.h"
#include "effects/increaseDamageEnemyMove.h"
#include "effects/limitCardToPlayEffect.h"
#include "effects/maintainExcessArmorEffect.h"
#include "effects/multiplierIfCardIsPresentInDeckEffect.h"
#include "util/debug.h"
#include <cassert>

EffectFactory::EffectFactory()
{
    // cards
    m_effectMap[EffectName::gainArmor] = makeGainArmorEffect;
    m_effectMap[EffectName::gainAttack] = makeGainAttackEffect;
    m_effectMap[EffectName::drawCards] = makeDrawCardsEffect;
    m_effectMap[EffectName::gainActions] = makeGainActionsEffect;
    m_effectMap[EffectName::buffIfCardPlayed] = makeBuffIfCardPlayedEffect;
    m_effectMap[EffectName::buffNextSpecifiedCardPlayedInTurn] =
            makeBuffNextSpecifiedCardPlayedInTurnEffect;
    m_effectMap[EffectName::maintainExcessArmor] = makeMaintainExcessArmorEffect;
    m_effectMap[EffectName::convertExcessArmorIntoAttack] = makeConvertExcessArmorIntoAttackEffect;
    m_effectMap[EffectName::multiplierIfCardIsPresentInDeck] =
            makeMultiplierIfCardIsPresentInDeckEffect;
    m_effectMap[EffectName::avoidDeath] = makeAvoidDeathEffect;
    m_effectMap[EffectName::buffOnPopulationEffect] = makeBuffOnPopulationEffect;

    // enemies
    m_effectMap[EffectName::takeHostage] = makeTakeHostageEffect;
    m_effectMap[EffectName::limitCardToPlay] = makeLimitCardToPlayEffect;
    m_effectMap[EffectName::addClogCardToDeck] = makeAddClogCardToDeck;
    m_effectMap[EffectName::increaseDamageEnemyMove] = makeIncreaseDamaeEnemyMove;
}

std::vector<std::unique_ptr<Effect>>
EffectFactory::makeEffectList(const std::vector<std::pair<EffectName, Target>>& effectDataList)
{
    std::vector<std::unique_ptr<Effect>> effectList;

    for (const auto& dataEffect : effectDataList)
    {
        auto mapIter = m_effectMap.find(dataEffect.first);

        if (mapIter == m_effectMap.end())
        {
            assert(false && "Unknown effect specifier");
            std::terminate();
        }

        effectList.emplace_back(std::move(mapIter->second(dataEffect.second)));
    }

    return effectList;
}

std::unique_ptr<Effect> EffectFactory::makeGainArmorEffect(Target target)
{
    return std::make_unique<GainArmorEffect>(target);
}

std::unique_ptr<Effect> EffectFactory::makeGainAttackEffect(Target target)
{
    return std::make_unique<GainAttackEffect>(target);
}

std::unique_ptr<Effect> EffectFactory::makeGainActionsEffect(Target target)
{
    return std::make_unique<GainActionsEffect>();
}

std::unique_ptr<Effect> EffectFactory::makeDrawCardsEffect(Target target)
{
    return std::make_unique<DrawCardsEffect>();
}

std::unique_ptr<Effect> EffectFactory::makeBuffIfCardPlayedEffect(Target target)
{
    return std::make_unique<BuffIfCardPlayedEffect>(target);
}

std::unique_ptr<Effect> EffectFactory::makeBuffNextSpecifiedCardPlayedInTurnEffect(Target target)
{
    return std::make_unique<BuffNextSpecifiedCardPlayedInTurnEffect>();
}

std::unique_ptr<Effect> EffectFactory::makeConvertExcessArmorIntoAttackEffect(Target target)
{
    return std::make_unique<ConvertExcessArmorIntoAttackEffect>(target);
}

std::unique_ptr<Effect> EffectFactory::makeMaintainExcessArmorEffect(Target target)
{
    return std::make_unique<MaintainExcessArmorEffect>(target);
}

std::unique_ptr<Effect> EffectFactory::makeMultiplierIfCardIsPresentInDeckEffect(Target target)
{
    return std::make_unique<MultiplierIfCardIsPresentInDeckEffect>();
}

std::unique_ptr<Effect> EffectFactory::makeAvoidDeathEffect(Target target)
{
    return std::make_unique<AvoidDeathEffect>();
}

std::unique_ptr<Effect> EffectFactory::makeBuffOnPopulationEffect(Target target)
{
    return std::make_unique<BuffOnPopulationEffect>(target);
}

std::unique_ptr<Effect> EffectFactory::makeLimitCardToPlayEffect(Target target)
{
    return std::make_unique<LimitCardToPlayEffect>();
}

std::unique_ptr<Effect> EffectFactory::makeTakeHostageEffect(Target target)
{
    return std::make_unique<HostageCardEffect>();
}

std::unique_ptr<Effect> EffectFactory::makeAddClogCardToDeck(Target target)
{
    return std::make_unique<AddClogCardToDeckEffect>();
}

std::unique_ptr<Effect> EffectFactory::makeIncreaseDamaeEnemyMove(Target target)
{
    return std::make_unique<IncreaseDamageEnemyMove>();
}
