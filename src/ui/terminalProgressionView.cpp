#include "terminalProgressionView.h"
#include "textWrap.h"

#include <format>

TerminalProgressionView::TerminalProgressionView(IOText& io) : m_io{io} {}

void TerminalProgressionView::showDivisor() const
{
    std::string str((m_mainWidth), '-');
    m_io.println(str);
}

void TerminalProgressionView::showProgressionDivisor() const
{
    std::string str((m_mainWidth), '=');
    m_io.println(color(AnsiColor::Yellow, str));
}

void TerminalProgressionView::showProgressionTitle() const
{
    showProgressionDivisor();
    m_io.println(std::format("{:^{}}", "THE ROAD AHEAD", m_mainWidth));
    m_io.println(std::format("{:^{}}", "Choose your path.", m_mainWidth));
    showProgressionDivisor();
}

void TerminalProgressionView::showCurrentNode(std::string_view previewDescription, int layer) const
{
    showDivisor();
    m_io.println(std::format("{:^{}}", std::format("Stage {} - {}", layer, previewDescription),
                             m_mainWidth));
    showDivisor();
}

void TerminalProgressionView::showPathOptions(
        const std::vector<const EventNode*>& optionsToRender) const
{
    for (const auto& line : m_progressionRenderer.renderPathOptions(optionsToRender))
    {
        m_io.println(line);
    }
}

int TerminalProgressionView::askPlayerPath(int limit)
{
    return m_io.promptInt("Where do you travel next:", limit) - 1;
}

void TerminalProgressionView::showSelectedPath(std::string_view previewDescription) const
{
    showDivisor();
    m_io.println(std::format("The caravan sets off: {}", previewDescription));
    showDivisor();
}

void TerminalProgressionView::showEndOfProgression() const
{
    showProgressionDivisor();
    m_io.println(std::format("{:^{}}", "THE ROAD ENDS HERE", m_mainWidth));
    showProgressionDivisor();
}

std::string TerminalProgressionView::color(AnsiColor color, const std::string& text)
{
    if (color == AnsiColor::None)
        return text;
    return std::string(colorCode(color)) + text + "\033[0m";
}

constexpr const char* TerminalProgressionView::colorCode(AnsiColor color)
{
    switch (color)
    {
    case AnsiColor::Red:
        return "\033[31m";
    case AnsiColor::Green:
        return "\033[32m";
    case AnsiColor::Yellow:
        return "\033[33m";
    default:
        return "";
    }
}