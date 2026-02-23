#ifndef IMATCHVIEW_H
#define IMATCHVIEW_H

#include <string>
#include <string_view>
#include <vector>

class CardInstance;
class Entity;
struct TurnData;
struct MatchData;
struct DamageResult;

class IMatchView
{
  public:
    virtual void showCurrentHand(const std::vector<const CardInstance*>& handToRender) const = 0;
    virtual void showMessage() = 0;
    virtual void showTurnState(const TurnData& turnData) const = 0;
    virtual void showMatchState(const MatchData& matchData) const = 0;
    virtual int askCardToPlay(int limit) = 0;
    virtual void showRecurringMatchStatus(const MatchData& matchData, const TurnData& turnData,
                                          const Entity& player, const Entity& enemy) const = 0;
    virtual void showDivisor() const = 0;
    virtual void showDamageResult(const DamageResult result) const = 0;
    virtual void showEffectMessage(const std::vector<std::string>& message) const = 0;
    virtual void showPlayedCardName(std::string_view name) const = 0;
    virtual void showPlayerTurnStart(const MatchData& matchData) const = 0;
    virtual void showFancyDivisor() const = 0;
    virtual void showEndOfTurn(const MatchData& matchData) const = 0;

  private:
};

#endif // IMATCHVIEW_H