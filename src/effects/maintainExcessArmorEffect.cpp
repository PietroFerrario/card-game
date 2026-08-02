#include "maintainExcessArmorEffect.h"
#include "combat/combatContext.h"
#include "util/debug.h"

void MaintainExcessArmorEffect::resolve(CombatContext& combatContext, const CardParams& values)
{
    combatContext.maintainPlayerArmor();
    DEBUG_LOG("Applied effect MaintainEccessArmor");
}
