#include "entities/enemies/bandits.h"
#include "entities/player.h"
#include "game_system/cardMatch.h"

#include "cards/cardInstance.h"
#include "deck/deckCombat.h"
#include "deck/deckEntry.h"
#include "deck/deckLoader.h"
#include "deck/deckPlayer.h"
#include "ui/handRenderer.h"
#include "ui/iotext.h"
#include "ui/terminalMatchView.h"
#include <iostream>
#include <string>

int main()
{

    // std::vector<DeckEntry> initialCardList{
    //     {"ShieldWarrior", 2}, {"Farmer", 2}, {"InexGuard", 2},     {"InexArcher", 2},
    //     {"Provisions", 1},    {"Horses", 1}, {"Quartermaster", 1}, {"Constable", 1},
    // };

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
    mainPlayer.setName("Il Troia");

    Bandits bandits{};

    IOText io{std::cout, std::cin};
    TerminalMatchView terminalMatchView{io};

    CardMatch cardMatch{terminalMatchView, mainPlayer, bandits};

    cardMatch.turnLoop();
}
