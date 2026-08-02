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
    maintainExcessArmor,
    avoidDeath
};

namespace effect
{
inline const std::unordered_map<std::string_view, EffectName> effectNameMap{
    {"gainArmor", EffectName::gainArmor},
    {"gainAttack", EffectName::gainAttack},
    {"drawCards", EffectName::drawCards},
    {"gainActions", EffectName::gainActions},
    {"buffIfCardPlayed", EffectName::buffIfCardPlayed},
    {"maintainExcessArmor", EffectName::maintainExcessArmor},
    {"avoidDeath", EffectName::avoidDeath},
    {"limitCardToPlay", EffectName::limitCardToPlay},
    {"takeHostage", EffectName::takeHostage},
    {"addClogCardToDeck", EffectName::addClogCardToDeck},
    {"increaseDamageEnemyMove", EffectName::increaseDamageEnemyMove}};
} // namespace effect
#endif // EFFECTNAME_H
