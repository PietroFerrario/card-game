#include "gainAttackEffect.h"
#include "cards/cardDefinition.h"
#include "cards/cardInstance.h"
#include "combat/combatContext.h"
#include "util/debug.h"

void GainAttackEffect::resolve(CombatContext& combatContext, const CardParams& values)
{
    combatContext.gainAttack(m_target, values.attack);
    DEBUG_LOG("Applied effect GainAttack");
}