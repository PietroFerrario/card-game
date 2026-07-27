#include "buffIfCardPlayedEffect.h"
#include "cards/cardDefinition.h"
#include "cards/cardInstance.h"
#include "cards/cardParams.h"
#include "combat/combatContext.h"
#include "deck/deckCombat.h"
#include "util/debug.h"

// This is single param buff -> Could be modified with multiple buff by the same loop in deckPlayer
void BuffIfCardPlayedEffect::resolve(CombatContext& combatContext, const CardParams& values)
{
    const auto& combatDeckView{combatContext.getDeckCombatView().getTurnPlayedView()};
    if (values.amount.has_value() && values.referenceId.has_value() &&
        values.upgradeCardParam.has_value())

    {
        auto foundCard =
            std::find_if(combatDeckView.begin(), combatDeckView.end(),
                         [&values](const CardInstance* playedCard)
                         {
                             return playedCard->getCardDefinition().getID() ==
                                    static_cast<std::string_view>(values.referenceId.value());
                         });

        if (foundCard != combatDeckView.end())
        {
            switch (values.upgradeCardParam.value())
            {
            case UpgradeCardParam::Attack:
                combatContext.gainAttack(m_target, values.amount.value());
                break;
            case UpgradeCardParam::Armor:
                combatContext.gainArmor(m_target, values.amount.value());
                break;
            case UpgradeCardParam::Action:
                combatContext.gainActions(values.amount.value());
                break;
            case UpgradeCardParam::Drawing:
                combatContext.drawMultipleCardFromEffect(values.amount.value());
                break;
            default:
                DEBUG_LOG("End of BufIfCardPlayedSwitch, nothing happens");
            }
        }
    }
}
