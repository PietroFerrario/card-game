#include "game_system/matchData.h"
#include "terminaMatchView.h"

TerminalMatchView::TerminalMatchView(IOText& io) : m_io{io} {}

void TerminalMatchView::showCurrentHand(const std::vector<const CardInstance*>& handToRender)
{
    m_io.printHand(m_handRenderer.renderHand(handToRender));
}

int TerminalMatchView::askCardToPlay(int limit)
{
    int selectedCardIndex{m_io.promptInt("Select a card to play:", limit) - 1};
    return selectedCardIndex;
}

void TerminalMatchView::showTurnState(TurnData& turnData)
{
    m_io.println(std::format("Remaining actions: {} \t Card played this turn {}",
                             turnData.playerRemainingActions, turnData.cardsPlayed));
}

void TerminalMatchView::showMatchState(MatchData& matchData)
{
    m_io.println(std::format("Current turn: {}", matchData.turnNumber));
}
