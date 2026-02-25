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

    int askCardToPlay(int limit) override;
    void showDamageResult(const DamageResult result) const override;
    void showEffectMessage(const std::vector<std::string>& message) const override;
    void showPlayedCardName(std::string_view name) const override;
    void showEnemyMove(std::string_view enemyName, std::string_view moveName) const override;
    void showPlayerTurnStart(const MatchData& matchData) const override;

    void showEndOfTurn(const MatchData& matchData) const override;
    void showEndOfMatch(const MatchData& matchData) const override;
    void showStartOfMatch(std::string_view enemyName) const override;
    void showDrawCards(const DrawData& drawData) const override;

  private:
    IOText& m_io;
    HandRenderer m_handRenderer;

    void showDivisor() const;
    void showFancyDivisor() const;
    void showMatchDivisor() const;
};

#endif // TERMINALMATCHVIEW_H