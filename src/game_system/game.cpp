#include "game.h"

#include <algorithm>
#include <cctype>
#include <ranges>

Game::Game(IOText& io) : m_io{io} {}

bool Game::isLost() const { return (m_mainPlayer.getHp() < 0); }

bool Game::isPlayerAlive() const { return m_mainPlayer.getHp() > 0; }

Player& Game::getMainPlayer() { return m_mainPlayer; }

const Player& Game::getMainPlayer() const { return m_mainPlayer; }

void Game::setMainPlayerName()
{
    std::string name{};

    do
    {
        m_io.promptln(name, "Enter your name: ");
    } while (!isValidName(name));

    m_mainPlayer.setName(name);
}

const bool Game::isValidName(std::string_view name) const
{
    return std::ranges::all_of(name, [](char ch) { return std::isalpha(ch) || std::isspace(ch); });
}

void Game::intro()
{
    m_io.println(m_text.getText("intro"));
    setMainPlayerName();
}

void Game::lossMessage() const { m_io.print(m_text.getText("outro")); }