#ifndef CARDPARAMSLOADER_H
#define CARDPARAMSLOADER_H

#include "cardParams.h"

#include <nlohmann/json.hpp>

namespace cardParamsLoader
{
inline CardParams loadCardParam(const nlohmann::json& jsonCardParam)
{
    return {.damage = jsonCardParam.at("damage").get<int>(),
            .armor = jsonCardParam.at("armor").get<int>(),
            .actions = {jsonCardParam.contains("actions") ? jsonCardParam.at("actions").get<int>()
                                                          : int{0}},
            .drawing = {jsonCardParam.contains("drawing") ? jsonCardParam.at("drawing").get<int>()
                                                          : int{0}},

            // upgradeCardParams check and adding
            .upgradeCardParam =
                {jsonCardParam.contains("upParams")
                     ? std::optional<UpgradeCardParam>{upgradeCardParam::upgradeCardParamMap.at(
                           jsonCardParam.at("upParams").get_ref<const std::string&>())}
                     : std::optional<UpgradeCardParam>{}},

            // amount check and adding
            .amount = {jsonCardParam.contains("amount")
                           ? std::optional<int>{jsonCardParam.at("amount").get<int>()}
                           : std::optional<int>{}},

            // referenceId check and adding
            .referenceId = {jsonCardParam.contains("referenceId")
                                ? std::optional<std::string>{jsonCardParam.at("referenceId")
                                                                 .get_ref<const std::string&>()}
                                : std::optional<std::string>{}}};
}
} // namespace cardParamsLoader

#endif // CARDPARAMSLOADER_H
