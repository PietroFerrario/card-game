#ifndef EFFECTNAME_H
#define EFFECTNAME_H

#include <string_view>
#include <unordered_map>

enum class EffectName
{
    gainArmor,
    gainAttack,
    gainActions,
    drawCards,
    limitCardToPlay,
    takeHostage,
    addClogCardToDeck,
    increaseDamageEnemyMove,
    buffIfCardPlayed,
    buffNextSpecifiedCardPlayedInTurn,
    maintainExcessArmor,
    convertExcessArmorIntoAttack,
    multiplierIfCardIsPresentInDeck,
    avoidDeath,
    buffOnPopulationEffect
};

namespace effect
{
inline const std::unordered_map<std::string_view, EffectName> effectNameMap{
        {"gainArmor", EffectName::gainArmor},
        {"gainAttack", EffectName::gainAttack},
        {"drawCards", EffectName::drawCards},
        {"gainActions", EffectName::gainActions},
        {"buffIfCardPlayed", EffectName::buffIfCardPlayed},
        {"buffNextSpecifiedCardPlayedInTurn", EffectName::buffNextSpecifiedCardPlayedInTurn},
        {"maintainExcessArmor", EffectName::maintainExcessArmor},
        {"convertExcessArmorIntoAttack", EffectName::convertExcessArmorIntoAttack},
        {"multiplierIfCardIsPresentInDeck", EffectName::multiplierIfCardIsPresentInDeck},
        {"avoidDeath", EffectName::avoidDeath},
        {"buffOnPopulation", EffectName::buffOnPopulationEffect},
        {"limitCardToPlay", EffectName::limitCardToPlay},
        {"takeHostage", EffectName::takeHostage},
        {"addClogCardToDeck", EffectName::addClogCardToDeck},
        {"increaseDamageEnemyMove", EffectName::increaseDamageEnemyMove}};
} // namespace effect
#endif // EFFECTNAME_H
