#ifndef MATCHEVENTDATA_H
#define MATCHEVENTDATA_H

#include "entities/enemies/enemyId.h"

#include <string>

struct MatchEventData
{
    EnemyId enemyId;
    std::string rewardListId;
};

#endif // MATCHEVENTDATA_H
