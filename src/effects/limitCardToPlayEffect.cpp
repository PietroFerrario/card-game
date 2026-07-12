#include "limitCardToPlayEffect.h"
#include "cards/cardInstance.h"
#include "combat/combatContext.h"
#include "util/debug.h"

void LimitCardToPlayEffect::resolve(CombatContext& combatContext, const CardParams& values)
{
    if (values.amount.has_value())
    {
        combatContext.limitCardToPlay(values.amount.value());
        DEBUG_LOG("Applied effect LimitCardToPlay");
    }
}
