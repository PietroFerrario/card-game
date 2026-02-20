#ifndef TERMINALMATCHVIEW_H
#define TERMINALMATCHVIEW_H

#include "IMatchView.h"
#include "handRenderer.h"
#include "iotext.h"

class TerminalMatchView : public IMatchView
{
  public:
    TerminalMatchView(IOText& io);

    void showCurrentHand(const std::vector<const CardInstance*>& handToRender) override;
    void showMessage() override;
    void showTurnState(TurnData& turnData) override;
    void showMatchState(MatchData& matchData) override;
    int askCardToPlay(int limit) override;

  private:
    IOText& m_io;
    HandRenderer m_handRenderer;
};

#endif // TERMINALMATCHVIEW_H