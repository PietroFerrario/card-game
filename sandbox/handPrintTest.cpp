#include "cards/cardInstance.h"
#include "deck/deckCombat.h"
#include "deck/deckEntry.h"
#include "deck/deckPlayer.h"
#include "factories/cardFactory.h"
#include "ui/cardRenderer.h"
#include "ui/iotext.h"

int main()
{
    IOText io{std::cout, std::cin};
    CardRenderer cardRenderer;

    const CardFactory factory;

    std::vector<DeckEntry> initialCardList{{"shieldWarrior", 2}};
    DeckPlayer mainDeckPlayer{initialCardList};

    DeckCombat mainDeckCombat{mainDeckPlayer, factory};

    mainDeckCombat.drawCard();
    mainDeckCombat.drawCard();

    io.printCard(cardRenderer.renderCard(mainDeckCombat.getCardInHand(0)));

    return 0;
}