#include "terminalRewardView.h"
#include "textWrap.h"

TerminalRewardView::TerminalRewardView(IOText& io, ICardFactory& cardFactory)
    : m_io{io}, m_cardFactory{cardFactory}, m_rewardsRenderer{m_cardFactory}
{
}

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

void TerminalRewardView::showStoryEventTitle(std::string_view storyEventName) const
{
    showFancyDivisor();
    m_io.println(
        std::format("{:^{}}", std::format("Story Event: {}!", storyEventName), m_mainWidth));

    showFancyDivisor();
}

void TerminalRewardView::showStoryEventDescription(std::string_view storyEventDescription) const
{
    for (const auto& line : wrapText(storyEventDescription, m_mainWidth))
    {
        m_io.println(line);
    }
}

RewardDecision TerminalRewardView::askPlayerReward(int limit)
{
    RewardDecision decision;
    int selectedOptionIndex{m_io.promptInt("Select your choice:", limit) - 1};
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
}

void TerminalRewardView::showSelectedRewardDescription(std::string_view rewardDescription) const
{
    m_io.println(std::format("{}", rewardDescription));
    showFancyDivisor();
};

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

int TerminalRewardView::askPlayerSelectRewardCard(int limit)
{
    int playerCardChoice;
    int selectedCardIndex{m_io.promptInt("Select a card to add to your deck", limit) - 1};

    playerCardChoice = selectedCardIndex;

    showFancyDivisor();
    return playerCardChoice;
}

int TerminalRewardView::askPlayerSelectUpgradeCard(int limit)
{
    int playerCardChoice;
    int selectedCardIndex{m_io.promptInt("Select a card from your current deck to upgrade", limit) -
                          1};

    playerCardChoice = selectedCardIndex;

    showFancyDivisor();
    return playerCardChoice;
}

void TerminalRewardView::showRandomCardSelection(
    const std::vector<const CardInstance*>& handToRender) const
{
    m_io.printHand(m_handRenderer.renderHand(handToRender));
}
