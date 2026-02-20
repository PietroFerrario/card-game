#ifndef MATCHDATA_H
#define MATCHDATA_H

enum class MatchState
{
    Running,
    PlayerWon,
    EnemyWon,
    Aborted
};

struct MatchData
{
    int turnNumber{0};
    MatchState matchState{MatchState::Running};
};

struct TurnData
{
    int playerRemainingActions{2};
    int cardsPlayed{0};
};

#endif // MATCHDATA_H