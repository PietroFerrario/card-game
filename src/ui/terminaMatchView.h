#ifndef TERMINALMATCHVIEW_H
#define TERMINALMATCHVIEW_H

#include "IMatchView.h"
#include "handRenderer.h"
#include "iotext.h"

class TerminalMatchView : public IMatchView
{
  public:
    TerminalMatchView(IOText& io);

    void showCurrentHand(const std::vector<const CardInstance*>& handToRender) override;
    void showCardEffects();
    void showMessage() override;
    void showTurnState(TurnData& turnData) override;
    void showMatchState(MatchData& matchData) override;
    void showRecurringMatchStatus(MatchData& matchData, TurnData& turnData, const Entity& player,
                                  const Entity& enemy) override;
    void showDivisor() override;
    int askCardToPlay(int limit) override;
    void showDamageResult(DamageResult result) override;
    void showEffectMessage(const std::vector<std::string>& message) override;
    void showPlayedCardName(std::string_view name) override;

  private:
    IOText& m_io;
    HandRenderer m_handRenderer;
};

#endif // TERMINALMATCHVIEW_H