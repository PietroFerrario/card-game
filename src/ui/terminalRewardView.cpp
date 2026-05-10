#include "terminalRewardView.h"

void TerminalRewardView::showDivisor() const
{
    std::string str((m_mainWidth), '-');
    m_io.println(str);
}

void TerminalRewardView::showDivisor() const
{
    std::string str((m_mainWidth), '-');
    m_io.println(str);
}

void TerminalRewardView::showFancyDivisor() const
{
    std::string str((m_mainWidth), '~');
    m_io.println(color(AnsiColor::Yellow, str));
}

void TerminalRewardView::showRewardText(std::string_view enemyName) const
{
    showMatchDivisor();
    m_io.println(
        std::format("{:^{}}", std::format("Reward for defeating {}!", enemyName), m_mainWidth));
    m_io.println(std::format(
        "{:^{}}", std::format("You can select one of the fellowing cards to add to your deck:"),
        m_mainWidth));
    showMatchDivisor();
}

RewardDecision TerminalRewardView::askPlayerReward(int limit)
{
    RewardDecision decision;
    int selectedCardIndex{
        m_io.promptInt("Select a card as a reward or press (0) for skipping the reward:", limit) -
        1};
    if (selectedCardIndex < 0)
    {
        decision.playerChoice = RewardChoice::SkipReward;
    }
    else
    {
        decision.playerChoice = RewardChoice::SelectReward;
        decision.selectedCard = selectedCardIndex;
    }
    return decision;
}

void TerminalRewardView::showReward(std::string_view cardSelected) const
{
    showFancyDivisor();
    m_io.println(
        std::format("You selected {} as a reward. He's joining your ranks!", cardSelected));
    showFancyDivisor();
}
