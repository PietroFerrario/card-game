#include "limitCardToPlayEffect.h"
#include "cards/cardInstance.h"
#include "combat/combatContext.h"
#include "util/debug.h"

void LimitCardToPlayEffect::resolve(CombatContext& combatContext, const CardParams& values)
{
    if (values.cardsLimit.has_value())
    {
        combatContext.limitCardToPlay(values.cardsLimit.value());
        DEBUG_LOG("Applied effect GainAction");
    }
}