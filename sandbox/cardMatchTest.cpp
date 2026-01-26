#include "game_system/cardMatch.h"
#include "entities/enemies/wolfPack.h"
#include "entities/player.h"

#include "cards/cardInstance.h"
#include "deck/deckCombat.h"
#include "deck/deckEntry.h"
#include "deck/deckPlayer.h"

int main()
{

    std::vector<DeckEntry> initialCardList{{"shieldWarrior", 2}};

    std::cout << "Instantiating Player from initial list of cards:\n";
    Player mainPlayer{initialCardList};
    mainPlayer.setName("Malliano");
    std::cout << "Player name: " << mainPlayer.getName() << "\n";

    std::cout << "Instantiating WolfPack Enemy from initial list of cards:\n";
    WolfPack pack{};
    std::cout << "Enemy name: " << pack.getName() << "\n";
    std::cout << "\n";

    std::cout << "Instantiating CardMatch from the Player and the Enemy:\n";
    CardMatch cardMatch{mainPlayer, pack};
    std::cout << "\n";

    std::cout << "Drawing 2 cards:\n";
    cardMatch.drawMultipleCards(2);
    std::cout << "\n";

    std::cout << "Trying to play 2 cards:\n";
    cardMatch.playCard(1);
    std::cout << "The player armor is now: " << mainPlayer.getArmor() << ".\n" << std::endl;
    cardMatch.playCard(0);
    std::cout << "The player armor is now: " << mainPlayer.getArmor() << ".\n" << std::endl;

    std::cout << "Trying to play 1 card when the hand is empty:\n";
    cardMatch.playCard(0);
    std::cout << "\n";

    std::cout << "Trying to draw an extra card when the deck is empty:\n";
    cardMatch.drawMultipleCards(1);
    std::cout << "\n";

    std::cout << "Enemy turn, only gaining defense: \n";
    cardMatch.enemyTurn();
    std::cout << "The armor of " << pack.getName() << " is now: " << pack.getArmor() << ".\n"
              << std::endl;

    return 0;
}