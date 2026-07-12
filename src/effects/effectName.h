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
    takeHostage
};

namespace effect
{
inline const std::unordered_map<std::string_view, EffectName> effectNameMap{
    {"gainArmor", EffectName::gainArmor},
    {"gainAttack", EffectName::gainAttack},
    {"drawCards", EffectName::drawCards},
    {"gainActions", EffectName::gainActions},
    {"limitCardToPlay", EffectName::limitCardToPlay},
    {"takeHostage", EffectName::takeHostage}};
} // namespace effect
#endif // EFFECTNAME_H
