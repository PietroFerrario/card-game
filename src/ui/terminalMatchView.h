#ifndef TERMINALMATCHVIEW_H
#define TERMINALMATCHVIEW_H

#include "IMatchView.h"
#include "handRenderer.h"
#include "iotext.h"

enum class AnsiColor
{
    None,
    Green,
    Red,
    Yellow
};

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

    PlayCardDecision askPlayerAction(int limit) override;
    void showPassingTurn() override;
    void showDamageResult(const DamageResult result) const override;
    void showEffectMessage(const std::vector<std::string>& message) const override;
    void showPlayedCardName(std::string_view name) const override;
    void showEnemyMove(std::string_view enemyName, std::string_view moveName,
                       std::string_view moveDescr) const override;
    void showPlayerTurnStart(const MatchData& matchData) const override;

    void showEndOfTurn(const MatchData& matchData) const override;
    void showEndOfMatch(const MatchData& matchData) const override;
    void showStartOfMatch(std::string_view enemyName) const override;
    void showDrawCards(const DrawData& drawData) const override;

  private:
    IOText& m_io;
    HandRenderer m_handRenderer;

    static constexpr int m_mainWidth{126};
    static constexpr int m_singleBoxWidth{40};
    static constexpr int m_boxes{3};
    static constexpr int m_singleEffectMessage{20};

    void showDivisor() const;
    void showFancyDivisor() const;
    void showMatchDivisor() const;

    static std::string color(AnsiColor color, const std::string& text);
    static constexpr const char* colorCode(AnsiColor color);
};

#endif // TERMINALMATCHVIEW_H