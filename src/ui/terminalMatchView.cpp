#include "entities\entity.h"
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
    m_io.println(std::format("Remaining actions: {} \t Card played this turn: {}",
                             turnData.playerRemainingActions, turnData.cardsPlayed));
}

// Implement showPlayerStats -> Current def and attack =)
void TerminalMatchView::showRecurringMatchStatus(MatchData& matchData, TurnData& turnData,
                                                 const Entity& player, const Entity& enemy)
{
    showDivisor();
    m_io.println(std::format("{:^28} | {:^28} | {:^28}",
                             std::format("Current turn: {}", matchData.turnNumber),
                             std::format("Remaining actions: {}", turnData.playerRemainingActions),
                             std::format("Card played this turn: {}", turnData.cardsPlayed)));

    showDivisor();
    m_io.println(std::format("{:^28} | {:^28} | {:^28}",
                             std::format("Player HP: {}", player.getHp()),
                             std::format("Player Attack: {}", player.getAttack()),
                             std::format("Player Armor: {}", player.getArmor())));
    showDivisor();
    m_io.println(std::format("{:^28} | {:^28} | {:^28}",
                             std::format("Enemy HP:  {}", enemy.getHp()),
                             std::format("Enemy Attack:  {}", enemy.getAttack()),
                             std::format("Enemy Armor:  {}", enemy.getArmor())));
    showDivisor();
}

void TerminalMatchView::showDivisor()
{
    std::string str((28 * 3 + 2 * 3), '-');
    m_io.println(str);
}

void TerminalMatchView::showMatchState(MatchData& matchData)
{
    m_io.println(std::format("Current turn: {}", matchData.turnNumber));
}

void TerminalMatchView::showMessage() {}