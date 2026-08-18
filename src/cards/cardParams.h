#ifndef CARDPARAMS_H
#define CARDPARAMS_H

#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

enum class UpgradeCardParam
{
    Attack,
    Armor,
    Action,
    Drawing,
};

/**
 * @brief Numeric parameters used to resolve gameplay effects.
 *
 * CardParams provides the numeric values consumed by Effect implementations
 * during resolution (e.g., damage, armor).
 *
 * The same parameter structure is used for both card effects and enemy moves,
 * allowing Effect behavior to remain stateless and reusable.
 */
struct CardParams
{
    // Common one
    int damage{0};
    int armor{0};

    // CardBased
    int actions{0};
    int drawing{0};
    std::optional<UpgradeCardParam> upgradeCardParam;

    std::optional<int> amount;
    std::optional<double> multiplier;
    std::optional<std::string> referenceId;

    CardParams& operator+=(const CardParams& other)
    {
        damage += other.damage;
        armor += other.armor;
        actions += other.actions;
        drawing += other.drawing;
        return *this;
    }
};

namespace upgradeCardParam
{
inline const std::unordered_map<std::string_view, UpgradeCardParam> upgradeCardParamMap{
        {"attack", UpgradeCardParam::Attack},
        {"armor", UpgradeCardParam::Armor},
        {"action", UpgradeCardParam::Action},
        {"drawing", UpgradeCardParam::Drawing}};

inline CardParams convertUpgradeCardParam(int amount, UpgradeCardParam upgradeCardParam)
{

    switch (upgradeCardParam)
    {
    case UpgradeCardParam::Attack:
        return {.damage = amount};
    case UpgradeCardParam::Armor:
        return {.armor = amount};
    case UpgradeCardParam::Action:
        return {.actions = amount};
    case UpgradeCardParam::Drawing:
        return {.drawing = amount};
    default:
        return {};
    }
}
}; // namespace upgradeCardParam

#endif // CARDPARAMS_H
