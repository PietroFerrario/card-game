#ifndef IMATCHVIEW_H
#define IMATCHVIEW_H

#include <vector>

class CardInstance;
class Entity;
struct TurnData;
struct MatchData;

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
    void displayDivisor();

  private:
};

#endif // IMATCHVIEW_H