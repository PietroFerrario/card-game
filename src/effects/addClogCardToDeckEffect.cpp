#include "addClogCardToDeckEffect.h"
#include "combat/combatContext.h"

#include <optional>

void AddClogCardToDeckEffect::resolve(CombatContext& combatContext, const CardParams& values)
{
    if (values.cardId.has_value() && values.amount.has_value())
    {
        combatContext.addCardToDeck(values.cardId.value(), values.amount.value());
    }
}
