#ifndef MATCHEVENTDATA_H
#define MATCHEVENTDATA_H

#include "deck/deckEntry.h"
#include "enemies/enemyId.h"

#include <string>
#include <vector>

struct MatchEventData
{
    EnemyId enemyId;
    std::vector<DeckEntry> rewardCardsList;
};

#endif // MATCHEVENTDATA_H