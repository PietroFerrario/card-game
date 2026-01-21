#ifndef GAME_H
#define GAME_H

#include "entities/player.h"
#include "ui/iotext.h"
#include "ui/text.h"

#include <memory>
#include <string>
#include <string_view>

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
    Player m_mainPlayer{};
};

#endif // GAME_H