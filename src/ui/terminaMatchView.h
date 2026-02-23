#ifndef TERMINALMATCHVIEW_H
#define TERMINALMATCHVIEW_H

#include "IMatchView.h"
#include "handRenderer.h"
#include "iotext.h"

class TerminalMatchView : public IMatchView
{
  public:
    TerminalMatchView(IOText& io);

    void showCurrentHand(const std::vector<const CardInstance*>& handToRender) const override;
    void showMessage() override;
    void showTurnState(const TurnData& turnData) const override;
    void showMatchState(const MatchData& matchData) const override;
    void showRecurringMatchStatus(const MatchData& matchData, const TurnData& turnData,
                                  const Entity& player, const Entity& enemy) const override;
    void showDivisor() const override;
    int askCardToPlay(int limit) override;
    void showDamageResult(const DamageResult result) const override;
    void showEffectMessage(const std::vector<std::string>& message) const override;
    void showPlayedCardName(std::string_view name) const override;
    void showPlayerTurnStart(const MatchData& matchData) const override;
    void showFancyDivisor() const override;
    void showEndOfTurn(const MatchData& matchData) const override;

  private:
    IOText& m_io;
    HandRenderer m_handRenderer;
};

#endif // TERMINALMATCHVIEW_H