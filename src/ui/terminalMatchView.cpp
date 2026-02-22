#include "combat/combatEvents.h"
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

void TerminalMatchView::showCardEffects() {}

void TerminalMatchView::showTurnState(TurnData& turnData)
{
    m_io.println(std::format("Remaining actions: {} \t Card played this turn: {}",
                             turnData.playerRemainingActions, turnData.cardsPlayed));
}

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

void TerminalMatchView::showDamageResult(DamageResult result)
{
    showDivisor();
    m_io.println(std::format(
        "{:^28} | {:^28} | {:^28}",
        std::format("{} is attacked for:  {}", result.target.getName(), result.requested),
        std::format("Blocked: {}", result.blocked),
        std::format("Sustained:  {}", result.hpDamage)));
    showDivisor();
}

void TerminalMatchView::showPlayedCardName(std::string_view name)
{
    showDivisor();
    m_io.println(std::format("Played card: {}", name));
}

void TerminalMatchView::showEffectMessage(const std::vector<std::string>& message)
{
    std::string formattedMessage;

    for (size_t i{0}; i < message.size(); ++i)
    {
        formattedMessage.append(std::format("{:^15}", message.at(i)));
        if (i + 1 < message.size())
        {
            formattedMessage.append(" | ");
        }
    }
    m_io.println(formattedMessage);

    showDivisor();
}

void TerminalMatchView::showMessage() {}