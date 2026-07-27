#include "terminalMatchView.h"
#include "combat/combatEvents.h"
#include "deck/deckCombat.h"
#include "entities\entity.h"
#include "game_system/matchData.h"

TerminalMatchView::TerminalMatchView(IOText& io) : m_io{io} {}

void TerminalMatchView::showStartOfMatch(std::string_view enemyName) const
{
    showMatchDivisor();
    m_io.println(color(
        AnsiColor::Red,
        std::format("{:^{}}", std::format("Match against {} started!", enemyName), m_mainWidth)));
    showMatchDivisor();
}

void TerminalMatchView::showCurrentHand(const std::vector<const CardInstance*>& handToRender) const
{
    m_io.printHand(m_handRenderer.renderHand(handToRender));
}

void TerminalMatchView::showPlayerTurnStart(const MatchData& matchData) const
{
    showFancyDivisor();
    m_io.println(color(AnsiColor::Yellow, std::format("Start of turn: {}", matchData.turnNumber)));
    showFancyDivisor();
}

void TerminalMatchView::showEndOfTurn(const MatchData& matchData) const
{
    showFancyDivisor();
    m_io.println(color(AnsiColor::Yellow, std::format("End of turn: {}", matchData.turnNumber)));
    showFancyDivisor();
}

void TerminalMatchView::showEndOfMatch(const MatchData& matchData) const
{
    showMatchDivisor();
    switch (matchData.matchState)
    {
    case MatchState::PlayerWon:
    {
        m_io.println(std::format("{:^{}}", "YOU HAVE DEFEATED YOUR ENEMY!!!", m_mainWidth));
        break;
    }
    case MatchState::EnemyWon:
    {
        m_io.println(
            std::format("{:^{}}", "THE ENEMY HAS PREVAILED... YOUR RUN ENDS HERE...", m_mainWidth));
        break;
    }
    case MatchState::MutualDestruction:
    {
        m_io.println(std::format("{:^{}}", "YOU HAVE VANQUISHED YOUR ENEMY!", m_mainWidth));
        m_io.println(
            std::format("{:^{}}", " Your vision is blurry, your hands are stiff.", m_mainWidth));
        m_io.println(std::format(
            "{:^{}}", "You look down and your glove comes back scarlet from touching your side...",
            m_mainWidth));
        m_io.println(std::format(
            "{:^{}}",
            "You have won, but was it worth the price? Only the gods will know the answer.",
            m_mainWidth));
        break;
    }
    }
    showMatchDivisor();
}

PlayCardDecision TerminalMatchView::askPlayerAction(int limit)
{
    PlayCardDecision decision;
    int selectedCardIndex{m_io.promptInt("Select a card to play or press (0) to pass:", limit) - 1};
    if (selectedCardIndex < 0)
    {
        decision.playerChoice = PlayerChoice::PassTurn;
    }
    else
    {
        decision.playerChoice = PlayerChoice::PlayCard;
        decision.selectedCard = selectedCardIndex;
    }
    return decision;
}

void TerminalMatchView::showPassingTurn()
{
    showDivisor();
    m_io.println("You decided to Pass. Your turn ends");
    showDivisor();
}

void TerminalMatchView::showTurnState(const TurnData& turnData) const
{
    m_io.println(std::format("Remaining actions: {} \t Card played this turn: {}",
                             turnData.playerRemainingActions, turnData.cardsPlayed));
}

void TerminalMatchView::showRecurringMatchStatus(const MatchData& matchData,
                                                 const TurnData& turnData, const Entity& player,
                                                 const Entity& enemy) const
{
    showDivisor();
    m_io.println(std::format(
        "{:^{}} | {:^{}} | {:^{}}", std::format("Current turn: {}", matchData.turnNumber),
        m_singleBoxWidth, std::format("Remaining actions: {}", turnData.playerRemainingActions),
        m_singleBoxWidth, std::format("Cards played this turn: {}", turnData.cardsPlayed),
        m_singleBoxWidth));

    // showDivisor();
    // m_io.println(std::format("{:^{}} | {:^{}} | {:^{}}",
    //                          std::format("Player HP: {}", player.getHp()), m_singleBoxWidth,
    //                          std::format("Player Attack: {}", player.getAttack()),
    //                          m_singleBoxWidth, std::format("Player Armor: {}",
    //                          player.getArmor()), m_singleBoxWidth));

    showDivisor();
    m_io.println(std::format(
        "{} | {} | {}",
        color(AnsiColor::Green, std::format("{:^{}}", std::format("Player HP: {}", player.getHp()),
                                            m_singleBoxWidth)),
        color(AnsiColor::Green,
              std::format("{:^{}}", std::format("Player Attack: {}", player.getAttack()),
                          m_singleBoxWidth)),
        color(AnsiColor::Green,
              std::format("{:^{}}", std::format("Player Armor: {}", player.getArmor()),
                          m_singleBoxWidth))));
    showDivisor();
    // m_io.println(std::format("{:^{}} | {:^{}} | {:^{}}",
    //                          std::format("Enemy HP:  {}", enemy.getHp()), m_singleBoxWidth,
    //                          std::format("Enemy Attack:  {}", enemy.getAttack()),
    //                          m_singleBoxWidth, std::format("Enemy Armor:  {}",
    //                          enemy.getArmor()), m_singleBoxWidth));

    m_io.println(std::format(
        "{} | {} | {}",
        color(AnsiColor::Red,
              std::format("{:^{}}", std::format("Enemy HP:  {}", enemy.getHp()), m_singleBoxWidth)),
        color(AnsiColor::Red,
              std::format("{:^{}}", std::format("Enemy Attack:  {}", enemy.getAttack()),
                          m_singleBoxWidth)),
        color(AnsiColor::Red,
              std::format("{:^{}}", std::format("Enemy Armor:  {}", enemy.getArmor()),
                          m_singleBoxWidth))));
    showDivisor();
}

void TerminalMatchView::showDivisor() const
{
    std::string str((m_mainWidth), '-');
    m_io.println(str);
}

void TerminalMatchView::showFancyDivisor() const
{
    std::string str((m_mainWidth), '~');
    m_io.println(color(AnsiColor::Yellow, str));
}

// void TerminalMatchView::showMatchDivisor() const
// {
//     std::string fragment("--✠--");
//     std::string str;
//     for (int i{0}; i < 18; ++i)
//     {
//         str.append(fragment);
//     }
//     m_io.println(str);
// }

void TerminalMatchView::showMatchDivisor() const
{
    std::string str((m_mainWidth), '=');
    m_io.println(color(AnsiColor::Red, str));
}

void TerminalMatchView::showMatchState(const MatchData& matchData) const
{
    m_io.println(std::format("Current turn: {}", matchData.turnNumber));
}

void TerminalMatchView::showDamageResult(const DamageResult result) const
{
    showDivisor();
    m_io.println(std::format(
        "{:>48} | {:^36} | {:^36}",
        std::format("{} is attacked for: {}   ", result.target.getName(), result.requested),
        std::format("Blocked: {}", result.blocked),
        std::format("Sustained:  {}", result.hpDamage)));
    showDivisor();
}

void TerminalMatchView::showPlayedCardName(std::string_view name) const
{
    showDivisor();
    m_io.println(std::format("{:^{}}", std::format("Played card: {}", name), m_mainWidth));
}

void TerminalMatchView::showEnemyMove(std::string_view enemyName, std::string_view moveName,
                                      std::string_view moveDescr) const
{
    showDivisor();
    m_io.println(
        color(AnsiColor::Red,
              std::format("{:^{}}", std::format("{} used: {}", enemyName, moveName), m_mainWidth)));
    m_io.println(std::format("{:^{}}", moveDescr, m_mainWidth));
}

void TerminalMatchView::showEffectMessage(const std::vector<std::string>& message) const
{
    std::string formattedMessage;

    for (size_t i{0}; i < message.size(); ++i)
    {
        formattedMessage.append(std::format("{:^{}}", message.at(i), m_singleEffectMessage));
        if (i + 1 < message.size())
        {
            formattedMessage.append(" | ");
        }
    }
    m_io.println(std::format("{:^{}}", formattedMessage, m_mainWidth));

    showDivisor();
}

void TerminalMatchView::showDrawCards(const DrawData& drawData) const
{
    showDivisor();

    std::string drawMessage;
    if (drawData.reshuffled)
    {
        drawMessage.append("Deck regenerated. ");
    }
    if (drawData.drawnCardsNames.empty())
    {
        drawMessage.append("No more cards to draw: empty deck and discard pile");
        return;
    }
    drawMessage.append("Drawn: ");
    for (size_t i{0}; i < drawData.drawnCardsNames.size(); ++i)
    {
        drawMessage.append(drawData.drawnCardsNames.at(i));
        if (i < drawData.drawnCardsNames.size() - 1)
            drawMessage.append(", ");
    }

    m_io.println(drawMessage);

    showDivisor();
}

void TerminalMatchView::showMessage() {}

constexpr const char* TerminalMatchView::colorCode(AnsiColor color)
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

std::string TerminalMatchView::color(AnsiColor color, const std::string& text)
{
    if (color == AnsiColor::None)
        return text;
    return std::string(colorCode(color)) + text + "\033[0m";
}
