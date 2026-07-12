#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <string>

struct GameConfig
{
    std::string id;
    int playerHp;
    int cardsDrawnPerTurn;
    int actionsPerTurn;
};

#endif // GAMECONFIG_H
