#ifndef TERMINALREWARDVIEW_H
#define TERMINALREWARDVIEW_H

/*
Need to merge the view at a certain point and refactor them unifying and avoiding repetitions
*/

#include "IRewardView.h"
#include "game_system/matchData.h"
#include "handRenderer.h"
#include "iotext.h"
#include "terminalMatchView.h" //For ansi color needs to be fixed and refactored

class TerminalRewardView : public IRewardView
{
  public:
    void showRewardText(std::string_view enemyName) const override;
    RewardDecision askPlayerReward(int limit) override;
    void showReward(std::string_view cardSelected) const override;

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

#endif // TERMINALREWARDVIEW_H