#include "buffNextSpecifiedCardPlayedInTurnEffect.h"
#include "cards/cardParams.h"
#include "combat/combatContext.h"
#include "util/debug.h"

void BuffNextSpecifiedCardPlayedInTurnEffect::resolve(CombatContext& combatContext,
                                                      const CardParams& values)
{
    if (values.referenceId.has_value() && values.amount.has_value())
        combatContext.addCardToDeck(values.referenceId.value(), values.amount.value());
    DEBUG_LOG("Applied effect BuffNextSpecifiedCardPlayedInTurn");
}