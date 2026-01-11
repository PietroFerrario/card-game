#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>
#include <string_view>

#include "player.h"
#include "iotext.h"
#include "text.h"

class Game
{

public:
    Game(IOText &io);

    void intro();
    void lossMessage() const;

    bool isLost() const;

    Player &getMainPlayer();
    const Player &getMainPlayer() const;
    void setMainPlayerName();
    const bool isValidName(std::string_view name) const;
    bool isPlayerAlive() const;

private:
    IOText &m_io;
    Text m_text{};
    Player m_main_player{};
};

#endif // GAME_H