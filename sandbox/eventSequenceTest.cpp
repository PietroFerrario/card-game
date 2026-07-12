#include "game_system/eventSequence.h"
#include "deck/deckLoader.h"
#include "entities/player.h"
#include "factories/cardFactory.h"
#include "game_system/configLoader.h"
#include "game_system/gameConfig.h"
#include "ui/iotext.h"
#include "ui/terminalMatchView.h"
#include "ui/terminalRewardView.h"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

int main()
{

#ifndef CARDGAME_DEBUG
    {
        std::ofstream("cardgame_log.txt", std::ios::out | std::ios::trunc); // wipe once
    }
#endif

    ConfigLoader configLoader;
    std::unordered_map<std::string, GameConfig> configMap{configLoader.loadConfigs()};

    CardFactory cardFactory;

    IOText io{std::cout, std::cin};
    TerminalMatchView terminalMatchView{io};
    TerminalRewardView terminalRewardView{io, cardFactory};

    DeckLoader deckLoader;

    std::string configId;
    std::string inputConfig;
    std::cout << "Welcome to the demo of an event sqeuence!\n\nSelect the "
                 "game configuration. Press (Enter) to continue with basic configuration.\nPress "
                 "(1) to select config1, press (2) for config2: \n";
    std::getline(std::cin, configId);

    if (inputConfig == "1")
    {
        configId = "config1";
    }
    else if (inputConfig == "2")
    {
        configId = "config2";
    }
    else
    {
        configId = "config0";
    }

    GameConfig gameConfig{configMap.at(configId)};

    std::cout << "Select the basic starting deck.\nPress (1) to select custom deck 1, "
                 "press(2) for custom deck 2: \n";

    std::string deckName;
    std::string inputDeck;
    int deckSelected{};

    std::getline(std::cin, inputDeck);

    if (inputDeck == "1")
    {
        deckName = "basicDeck2";
    }
    else if (inputDeck == "2")
    {
        deckName = "basicDeck3";
    }
    else
    {
        deckName = "basicDeck";
    }

    Player mainPlayer{deckLoader.loadDeck(deckName), gameConfig.playerHp};
    mainPlayer.setName("Malliano");

    EventSequence eventSequence{gameConfig, terminalMatchView, terminalRewardView, cardFactory,
                                mainPlayer};
    eventSequence.resolveEventSequence();

    std::cout << "Congratulations!!!\n You have completed the Demo for CardGame(Non abbiamo ancora "
                 "il nome dio canaja)";
    return 0;
}
