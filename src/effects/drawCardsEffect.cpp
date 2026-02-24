#include "drawCardsEffect.h"
#include "cards/cardDefinition.h"
#include "cards/cardInstance.h"
#include "combat/combatContext.h"
#include "util/debug.h"

void DrawCardsEffect::resolve(CombatContext& combatContext, const CardParams& values)
{
    combatContext.drawCards(values.drawing);
    DEBUG_LOG("Applied effect DrawCards");
}