#include "hostageCardEffect.h"
#include "cards/cardInstance.h"
#include "combat/combatContext.h"
#include "util/debug.h"

void HostageCardEffect::resolve(CombatContext& combatContext, const CardParams& values)
{
    combatContext.takeCardHostage();
    DEBUG_LOG("Applied effect GainAction");
}