#ifndef MATCHDATA_H
#define MATCHDATA_H

#include <optional>

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
    int initialCardsToDraw{5};

    // enemy based

    std::optional<int> cardsToPlayLimit;
};

// Refactor for both playing card and refactor
enum class PlayerChoice
{
    PlayCard,
    PassTurn,
};

struct PlayCardDecision
{
    PlayerChoice playerChoice{PlayerChoice::PassTurn};
    std::optional<int> selectedCard;
};

enum class RewardChoice
{
    SelectReward,
    SkipReward,
};

struct RewardDecision
{
    RewardChoice playerChoice{RewardChoice::SkipReward};
    std::optional<int> selectedOption;
};

#endif // MATCHDATA_H