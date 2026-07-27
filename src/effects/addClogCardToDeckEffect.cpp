#include "addClogCardToDeckEffect.h"
#include "combat/combatContext.h"

#include <optional>

void AddClogCardToDeckEffect::resolve(CombatContext& combatContext, const CardParams& values)
{
    if (values.referenceId.has_value() && values.amount.has_value())
    {
        combatContext.addCardToDeck(values.referenceId.value(), values.amount.value());
    }
}
