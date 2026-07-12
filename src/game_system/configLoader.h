#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include "gameConfig.h"

#include <nlohmann/json.hpp>
#include <string>
#include <string_view>
#include <unordered_map>

class ConfigLoader
{
  public:
    ConfigLoader();

    std::unordered_map<std::string, GameConfig> loadConfigs();

  private:
    nlohmann::json m_data{};
};

#endif // CONFIGLOADER_H
