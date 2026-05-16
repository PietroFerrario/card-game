#include "terminalRewardView.h"

TerminalRewardView::TerminalRewardView(IOText& io) : m_io{io} {}

void TerminalRewardView::showDivisor() const
{
    std::string str((m_mainWidth), '-');
    m_io.println(str);
}

void TerminalRewardView::showRewardPhaseDivisor() const
{
    std::string str((m_mainWidth), '=');
    m_io.println(str);
}

void TerminalRewardView::showFancyDivisor() const
{
    std::string str((m_mainWidth), '~');
    m_io.println(color(AnsiColor::Yellow, str));
}

void TerminalRewardView::showRewardOptions(
    const std::vector<RewardOption>& rewardListToRender) const
{
    m_io.printRewardsList(m_rewardsRenderer.renderRewards(rewardListToRender));
}

void TerminalRewardView::showRewardText(std::string_view enemyName) const
{
    showRewardPhaseDivisor();
    m_io.println(
        std::format("{:^{}}", std::format("Rewards for defeating {}!", enemyName), m_mainWidth));
    m_io.println(std::format("{:^{}}", std::format("Only one can be claimed."), m_mainWidth));
    showRewardPhaseDivisor();
}

RewardDecision TerminalRewardView::askPlayerReward(int limit)
{
    RewardDecision decision;
    int selectedOptionIndex{
        m_io.promptInt("Select a reward or press (0) for skipping the reward:", limit) - 1};
    if (selectedOptionIndex < 0)
    {
        decision.playerChoice = RewardChoice::SkipReward;
    }
    else
    {
        decision.playerChoice = RewardChoice::SelectReward;
        decision.selectedOption = selectedOptionIndex;
    }
    return decision;
}

void TerminalRewardView::showSkippingReward() const
{
    showFancyDivisor();
    m_io.print("You skipped the reward!");
}

void TerminalRewardView::showSelectedReward(std::string_view rewardNameSelected) const
{
    showFancyDivisor();
    m_io.println(std::format("You selected {} as a reward.", rewardNameSelected));
    showFancyDivisor();
}

std::string TerminalRewardView::color(AnsiColor color, const std::string& text)
{
    if (color == AnsiColor::None)
        return text;
    return std::string(colorCode(color)) + text + "\033[0m";
}

constexpr const char* TerminalRewardView::colorCode(AnsiColor color)
{
    switch (color)
    {
    case AnsiColor::Red:
    {
        return "\033[31m";
    }
    case AnsiColor::Green:
    {
        return "\033[32m";
    }
    case AnsiColor::Yellow:
    {
        return "\033[33m";
    }
    default:
        return "";
    }
}
