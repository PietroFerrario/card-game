#include "avoidDeathEffect.h"
#include "combat/combatContext.h"
#include "util/debug.h"

void AvoidDeathEffect::resolve(CombatContext& combatContext, const CardParams& values)
{
    combatContext.avoidPlayerDeath();
    DEBUG_LOG("Applied effect AvoidDeath");
}
