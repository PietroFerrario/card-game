#include "configLoader.h"

#include <cassert>
#include <fstream>

using json = nlohmann::json;

ConfigLoader::ConfigLoader()
{
    std::ifstream f("data/gameConfig.json");
    assert(f.is_open() && "Failed to open gameConfig json");
    m_data = json::parse(f);
}

std::unordered_map<std::string, GameConfig> ConfigLoader::loadConfigs()
{
    std::unordered_map<std::string, GameConfig> configMap;

    const json& configList = m_data.at("configList");

    for (const auto& configData : configList)
    {
        GameConfig config{configData.at("id").get_ref<const std::string&>(),
                          configData.at("playerHp").get<int>(),
                          configData.at("cardsDrawnPerTurn").get<int>(),
                          configData.at("actionsPerTurn").get<int>()};

        std::string id{config.id};

        configMap.emplace(std::move(id), std::move(config));
    }

    return configMap;
}
