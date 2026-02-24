#ifndef MATCHDATA_H
#define MATCHDATA_H

enum class MatchState
{
    Running,
    PlayerWon,
    EnemyWon,
    MutualDestruction,
    Aborted
};

struct MatchData
{
    int turnNumber{1};
    MatchState matchState{MatchState::Running};
};

struct TurnData
{
    int playerRemainingActions{2};
    int cardsPlayed{0};
    int initialCardsToDraw{2};
};

#endif // MATCHDATA_H