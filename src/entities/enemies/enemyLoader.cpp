#include "enemyLoader.h"

#include <cassert>
#include <fstream>
#include <optional>

using json = nlohmann::json;

EnemyLoader::EnemyLoader()
{
    std::ifstream f("data/enemies.json");
    assert(f.is_open() && "Failed to open enemy json");
    m_data = json::parse(f);
}

std::unordered_map<std::string, EnemyData> EnemyLoader::loadEnemies()
{
    std::unordered_map<std::string, EnemyData> enemyMap;

    const json& enemyList = m_data.at("enemyList");

    for (const auto& jsonEnemyData : enemyList)
    {
        EnemyData enemy{jsonEnemyData.at("id").get_ref<const std::string&>(),
                        jsonEnemyData.at("name").get_ref<const std::string&>(),
                        jsonEnemyData.at("hp").get<int>(),
                        makeEnemyMovesDataList(jsonEnemyData.at("movesList"))};

        std::string id{enemy.id};
        enemyMap.emplace(std::move(id), std::move(enemy));
    }

    return enemyMap;
}

std::vector<EnemyMoveData> EnemyLoader::makeEnemyMovesDataList(const json& jsonMoveList)
{
    std::vector<EnemyMoveData> enemyMoveDataList;
    for (const auto& jsonMove : jsonMoveList)
    {
        enemyMoveDataList.emplace_back(
            jsonMove.at("moveName").get_ref<const std::string&>(),
            jsonMove.at("moveDescription").get_ref<const std::string&>(),
            jsonMove.at("damage").get<int>(), jsonMove.at("armor").get<int>(),

            // amount check and adding
            jsonMove.contains("amount") ? std::optional<int>{jsonMove.at("amount").get<int>()}
                                        : std::optional<int>{},

            // referenceId check and adding
            jsonMove.contains("referenceId")
                ? std::optional<std::string>{jsonMove.at("referenceId")
                                                 .get_ref<const std::string&>()}
                : std::optional<std::string>{},

            makeMoveEffectsDataList(jsonMove.at("effectList")));
    }
    return enemyMoveDataList;
}

std::vector<std::pair<EffectName, Target>>
EnemyLoader::makeMoveEffectsDataList(const json& jsonEffectList)
{
    std::vector<std::pair<EffectName, Target>> moveEffectList;

    for (const auto& jsonEffect : jsonEffectList)
    {
        EffectName effectName{
            effect::effectNameMap.at(jsonEffect.at("effect").get_ref<const std::string&>())};

        const auto& targetJson{jsonEffect.at("target")};
        Target target{targetJson.is_null()
                          ? Target::Self
                          : target::targetMap.at(targetJson.get_ref<const std::string&>())};

        moveEffectList.emplace_back(std::pair<EffectName, Target>{effectName, target});
    }
    return moveEffectList;
}
