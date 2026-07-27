#include "enemyFactory.h"
#include "cards/cardParams.h"
#include "entities/enemies/enemyMove.h"

#include <vector>

EnemyFactory::EnemyFactory(std::unordered_map<std::string, EnemyData> enemyMap)
    : m_enemyMap{std::move(enemyMap)}
{
}

std::unique_ptr<Enemy> EnemyFactory::makeEnemy(std::string enemyId)
{
    EnemyData enemyData{m_enemyMap.at(enemyId)};
    std::vector<EnemyMove> enemyMovesList;

    for (auto& moveData : enemyData.moveList)
    {
        CardParams cardParams{moveData.damage, moveData.armor};
        cardParams.amount = moveData.amount;
        cardParams.referenceId = moveData.referenceId;

        enemyMovesList.emplace_back(std::move(moveData.moveName),
                                    std::move(moveData.moveDescription), cardParams,
                                    m_effectFactory.makeEffectList(moveData.effectList));
    }
    return {std::make_unique<Enemy>(enemyData.name, enemyData.hp, std::move(enemyMovesList))};
}
