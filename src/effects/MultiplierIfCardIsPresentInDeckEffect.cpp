#include "multiplierIfCardIsPresentInDeckEffect.h"
#include "combat/combatContext.h"
#include "deck/deckPlayer.h"
#include "util/debug.h"

void MultiplierIfCardIsPresentInDeckEffect::resolve(CombatContext& combatContext,
                                                    const CardParams& values)
{
    if (values.referenceId.has_value() && values.upgradeCardParam.has_value() &&
        values.multiplier.has_value() &&
        combatContext.getDeckPlayerView().isCardPresent(values.referenceId.value()))
    {
        switch (values.upgradeCardParam.value())
        {
        case UpgradeCardParam::Attack:
            combatContext.addAttackMultiplier(values.multiplier.value());
            break;
        case UpgradeCardParam::Armor:
            combatContext.addArmorMultiplier(values.multiplier.value());
            break;
        default:
            DEBUG_LOG("End of MultiplierIfCardIsPresentInDeckEffect, nothing happens");
        }
    }
}