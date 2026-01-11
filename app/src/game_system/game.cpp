#include "game.h"

#include <ranges>
#include <algorithm>
#include <cctype>


Game::Game(IOText& io): m_io{io}{}

bool Game::isLost() const {
    return(m_main_player.getHp()<0);
}

bool Game::isPlayerAlive() const{
    return m_main_player.getHp()>0;
}

Player& Game::getMainPlayer(){
    return m_main_player;
}

const Player& Game::getMainPlayer () const {
    return m_main_player;
}

void Game::setMainPlayerName(){
    std::string name {};
    
    do{
        m_io.promptln(name, "Enter your name: ");
    }while(!isValidName(name));

    m_main_player.setName(name);
}

const bool Game::isValidName(std::string_view name) const {
    return std::ranges::all_of(name, [](char ch) {
        return std::isalpha(ch) || std::isspace(ch);
    });
}

void Game::intro() {
    m_io.println("Welcome traveler, what is your name?");
    setMainPlayerName();
}

void Game::lossMessage() const {
    m_io.print(m_text.getText("outro"));
}