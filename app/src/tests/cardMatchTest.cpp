#include "game_system/cardMatch.h"
#include "entities/enemies/enemy.h"
#include "entities/player.h"

#include "cards/cardInstance.h"
#include "deck/deckCombat.h"
#include "deck/deckEntry.h"
#include "deck/deckPlayer.h"

int main()
{

    std::vector<DeckEntry> initialCardList{{"shieldWarrior", 2}};

    Player mainPlayer{initialCardList};
    Enemy enemy{10, 10};

    CardMatch cardMatch{mainPlayer, enemy};

    cardMatch.playCard(1);
    cardMatch.playCard(1);
    cardMatch.playCard(1);

    return 0;
}