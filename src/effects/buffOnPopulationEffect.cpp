#include "buffOnPopulationEffect.h"
#include "cards/cardParams.h"
#include "combat/combatContext.h"
#include "util/debug.h"

void BuffOnPopulationEffect::resolve(CombatContext& combatContext, const CardParams& values)
{

    int multiplier{(combatContext.getPlayerPopulation() - values.amount.value()) /
                   values.amount.value()};
    if (values.upgradeCardParam.has_value() && multiplier > 0)
    {
        switch (values.upgradeCardParam.value())
        {
        case UpgradeCardParam::Attack:
            combatContext.gainAttack(m_target, values.damage * multiplier);
            break;
        case UpgradeCardParam::Armor:
            combatContext.gainArmor(m_target, values.armor * multiplier);
            break;
        case UpgradeCardParam::Action:
            combatContext.gainActions(values.actions * multiplier);
            break;
        case UpgradeCardParam::Drawing:
            combatContext.drawMultipleCardFromEffect(values.drawing * multiplier);
            break;
        default:
            DEBUG_LOG("End of BuffOnPopulationSwitch, nothing happens");
        }
    }

    DEBUG_LOG("Applied effect BuffOnPopulation");
}
