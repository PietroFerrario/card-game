#include "increaseDamageEnemyMove.h"
#include "combat/combatContext.h"
#include "util/debug.h"

void IncreaseDamageEnemyMove::resolve(CombatContext& combatContext, const CardParams& values)
{
    if (values.referenceId.has_value() && values.amount.has_value())
    {
        combatContext.increaseDamageEnemyMove(values.referenceId.value(), values.amount.value());
    }
    else
    {
        DEBUG_LOG("increaseDamageEnemyMove doesn't have an id");
    }
}
