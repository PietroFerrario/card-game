#ifndef TERMINALREWARDVIEW_H
#define TERMINALREWARDVIEW_H

/*
Need to merge the view at a certain point and refactor them unifying and avoiding repetitions
*/

#include "IRewardView.h"
#include "cards/cardInstance.h"
#include "factories/ICardFactory.h"
#include "game_system/matchData.h"
#include "handRenderer.h"
#include "iotext.h"
#include "rewardsRenderer.h"
#include "terminalMatchView.h" //For ansi color needs to be fixed and refactored

#include <vector>

class TerminalRewardView : public IRewardView
{
  public:
    TerminalRewardView(IOText& io, ICardFactory& cardFactory);

    void showRewardText(std::string_view enemyName) const override;
    RewardDecision askPlayerReward(int limit) override;
    void showSkippingReward() const override;
    void showSelectedReward(std::string_view rewardNameSelected) const override;
    void showSelectedRewardDescription(std::string_view rewardDescription) const override;

    void showRewardOptions(const std::vector<RewardOption>& rewardListToRender) const override;

    int askPlayerSelectRewardCard(int limit) override;
    void
    showRandomCardSelection(const std::vector<const CardInstance*>& handToRender) const override;

  private:
    ICardFactory& m_cardFactory;
    IOText& m_io;
    HandRenderer m_handRenderer;
    RewardsRenderer m_rewardsRenderer;

    static constexpr int m_mainWidth{126};
    static constexpr int m_singleBoxWidth{40};
    static constexpr int m_boxes{3};
    static constexpr int m_singleEffectMessage{20};

    void showDivisor() const;
    void showFancyDivisor() const;
    void showRewardPhaseDivisor() const;

    static std::string color(AnsiColor color, const std::string& text);
    static constexpr const char* colorCode(AnsiColor color);
};

#endif // TERMINALREWARDVIEW_H
