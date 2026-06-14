#include "game_system/eventSequence.h"
#include "deck/deckLoader.h"
#include "entities/player.h"
#include "factories/cardFactory.h"
#include "ui/iotext.h"
#include "ui/terminalMatchView.h"
#include "ui/terminalRewardView.h"

#include <fstream>
#include <iostream>
#include <string>

int main()
{

#ifndef CARDGAME_DEBUG
    {
        std::ofstream("cardgame_log.txt", std::ios::out | std::ios::trunc); // wipe once
    }
#endif

    CardFactory cardFactory;

    IOText io{std::cout, std::cin};
    TerminalMatchView terminalMatchView{io};
    TerminalRewardView terminalRewardView{io, cardFactory};

    DeckLoader deckLoader;

    std::string deckName;
    std::cout << "Welcome to the demo of a combat instance!\n Press (Enter) to continue: you will "
                 "select the basic starting deck.\n Press (1) if you want to select custom deck 1, "
                 "or (2) for custom deck 2";
    std::string input;
    int deckSelected{};

    std::getline(std::cin, input);

    if (input == "1")
    {
        deckName = "basicDeck2";
    }
    else if (input == "2")
    {
        deckName = "basicDeck3";
    }
    else
    {
        deckName = "basicDeck";
    }

    Player mainPlayer{deckLoader.loadDeck(deckName)};
    mainPlayer.setName("Malliano");

    EventSequence eventSequence{terminalMatchView, terminalRewardView, cardFactory, mainPlayer};
    eventSequence.resolveEventSequence();

    return 0;
}
