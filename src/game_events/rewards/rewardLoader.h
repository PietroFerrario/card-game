#ifndef REWARDLOADER_H
#define REWARDLOADER_H

#include "rewardOption.h"
#include "rewardOptionData.h"
#include <vector>

#include <nlohmann/json.hpp>

class RewardLoader
{
  public:
    RewardLoader();
    td::vector<RewardOption> RewardLoader::loadRewards();

  private:
    nlohmann::json m_data{};
};

#endif // REWARDLOADER_H