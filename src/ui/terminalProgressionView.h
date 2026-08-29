#ifndef TERMINALPROGRESSIONVIEW_H
#define TERMINALPROGRESSIONVIEW_H

#include "IProgressionView.h"
#include "iotext.h"
#include "progressionRenderer.h"
#include "terminalMatchView.h" // AnsiColor — same borrow as TerminalRewardView

#include <string_view>
#include <vector>

class TerminalProgressionView : public IProgressionView
{
  public:
    TerminalProgressionView(IOText& io);

    void showProgressionTitle() const override;
    void showCurrentNode(std::string_view previewDescription, int layer) const override;

    void showPathOptions(const std::vector<const EventNode*>& optionsToRender) const override;
    int askPlayerPath(int limit) override;

    void showSelectedPath(std::string_view previewDescription) const override;
    void showEndOfProgression() const override;

  private:
    IOText& m_io;
    ProgressionRenderer m_progressionRenderer;

    static constexpr int m_mainWidth{126};

    void showDivisor() const;
    void showProgressionDivisor() const;

    static std::string color(AnsiColor color, const std::string& text);
    static constexpr const char* colorCode(AnsiColor color);
};

#endif // TERMINALPROGRESSIONVIEW_H