#include "gainArmorEffect.h"
#include "cards/cardDefinition.h"
#include "cards/cardInstance.h"
#include "combat/combatContext.h"
#include "util/debug.h"

void GainArmorEffect::resolve(CombatContext& combatContext, const EffectParams& values)
{
    combatContext.gainArmor(m_target, values.armor);
    DEBUG_LOG("Applied effect GainArmor");
}