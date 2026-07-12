#ifndef ENEMYLOADER_H
#define ENEMYLOADER_H

#include "combat/combatTarget.h"
#include "effects/effectName.h"
#include "enemyData.h"

#include <nlohmann/json.hpp>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class EnemyLoader
{
  public:
    EnemyLoader();

    std::unordered_map<std::string, EnemyData> loadEnemies();

  private:
    std::vector<EnemyMoveData> makeEnemyMovesDataList(const nlohmann::json& jsonMoveList);
    std::vector<std::pair<EffectName, Target>>
    makeMoveEffectsDataList(const nlohmann::json& jsonEffectList);

    nlohmann::json m_data{};
};

#endif // ENEMYLOADER_H
