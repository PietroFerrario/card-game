#include "buffNextSpecifiedCardPlayedInTurnEffect.h"
#include "cards/cardParams.h"
#include "combat/combatContext.h"
#include "util/debug.h"

void BuffNextSpecifiedCardPlayedInTurnEffect::resolve(CombatContext& combatContext,
                                                      const CardParams& values)
{
    if (values.referenceId.has_value() && values.multiplier.has_value())
        combatContext.addPendingBuff(values.referenceId.value(), values);
    DEBUG_LOG("Applied effect BuffNextSpecifiedCardPlayedInTurn");
}