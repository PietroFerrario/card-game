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
    virtual void showCurrentHand(const std::vector<const CardInstance*>& handToRender) = 0;
    virtual void showMessage() = 0;
    virtual void showTurnState(TurnData& turnData) = 0;
    virtual void showMatchState(MatchData& matchData) = 0;
    virtual int askCardToPlay(int limit) = 0;
    virtual void showRecurringMatchStatus(MatchData& matchData, TurnData& turnData,
                                          const Entity& player, const Entity& enemy) = 0;
    virtual void showDivisor() = 0;
    virtual void showDamageResult(DamageResult result) = 0;
    virtual void showEffectMessage(const std::vector<std::string>& message) = 0;
    virtual void showPlayedCardName(std::string_view name) = 0;

  private:
};

#endif // IMATCHVIEW_H