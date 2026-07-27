#ifndef ENEMYDATA_H
#define ENEMYDATA_H

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
    int damage{0};
    int armor{0};
    std::optional<int> amount;
    std::optional<std::string> referenceId;
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
