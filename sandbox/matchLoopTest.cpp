#include "entities/enemies/wolfPack.h"
#include "entities/player.h"
#include "game_system/cardMatch.h"

#include "cards/cardInstance.h"
#include "deck/deckCombat.h"
#include "deck/deckEntry.h"
#include "deck/deckPlayer.h"
#include "ui/handRenderer.h"
#include "ui/iotext.h"
#include "ui/terminaMatchView.h"

int main()
{

    std::vector<DeckEntry> initialCardList{{"shieldWarrior", 10}};

    Player mainPlayer{initialCardList};
    mainPlayer.setName("Malliano");

    WolfPack pack{};

    IOText io{std::cout, std::cin};
    TerminalMatchView terminalMatchView{io};

    CardMatch cardMatch{terminalMatchView, mainPlayer, pack};

    cardMatch.turnLoop();
}
