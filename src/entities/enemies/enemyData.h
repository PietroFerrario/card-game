#ifndef ENEMYDATA_H
#define ENEMYDATA_H

#include "cards/cardParams.h"
#include "combat/combatTarget.h"
#include "effects/effectName.h"

#include <optional>
#include <string>
#include <utility>
#include <vector>

struct EnemyMoveData
{
    std::string moveName;
    std::string moveDescription;
    CardParams cardParams;
    std::vector<std::pair<EffectName, Target>> effectList;
};

struct EnemyData
{
    std::string id;
    std::string name;
    int hp;
    std::vector<EnemyMoveData> moveList{};
};

#endif // ENEMYDATA_H
