#include "gainActionsEffect.h"
#include "cards/cardInstance.h"
#include "combat/combatContext.h"
#include "util/debug.h"

void GainActionsEffect::resolve(CombatContext& combatContext, const CardParams& values)
{
    combatContext.gainActions(values.actions);
    DEBUG_LOG("Applied effect GainAction");
}