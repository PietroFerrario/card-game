#include "cards/cardInstance.h"
#include "deck/deckCombat.h"
#include "deck/deckEntry.h"
#include "deck/deckPlayer.h"
#include "factories/cardFactory.h"
#include "ui/cardRenderer.h"
#include "ui/handRenderer.h"
#include "ui/iotext.h"

int main()
{
    IOText io{std::cout, std::cin};
    CardRenderer cardRenderer;
    HandRenderer handRenderer;

    const CardFactory factory;

    std::vector<DeckEntry> initialCardList{{"shieldWarrior", 9}};
    DeckPlayer mainDeckPlayer{initialCardList};

    DeckCombat mainDeckCombat{mainDeckPlayer, factory};

    mainDeckCombat.drawCard();
    mainDeckCombat.drawCard();
    mainDeckCombat.drawCard();
    mainDeckCombat.drawCard();
    mainDeckCombat.drawCard();
    mainDeckCombat.drawCard();
    mainDeckCombat.drawCard();

    io.print("Showing a single card: \n");
    io.printCards(cardRenderer.renderCard(mainDeckCombat.getCardInHand(0)));
    io.print("\n");

    io.print("Showing the full player hand: \n");
    io.printCards(handRenderer.renderHand(mainDeckCombat.getHandView()));

    return 0;
}