#include "cards/cardInstance.h"
#include "deck/deckCombat.h"
#include "deck/deckEntry.h"
#include "deck/deckPlayer.h"
#include "factories/cardFactory.h"

#include <memory>
#include <vector>

int main()
{
    const CardFactory factory;
    std::cout << "Creating single card from the card factory: \n";
    std::unique_ptr<CardInstance> shieldWarrior = factory.makeSingleCard("shieldWarrior");
    std::cout << "\n";

    std::vector<DeckEntry> initialCardList{{"shieldWarrior", 2}};

    std::cout << "Instantiating PlayerDeck from initial list of cards: \n";
    DeckPlayer mainDeckPlayer{initialCardList};
    std::cout << "\n";

    std::cout << "Instantiating DeckCombat of card instances from the playerDeck: \n";
    DeckCombat mainDeckCombat{mainDeckPlayer, factory};
    std::cout << "\n";

    std::cout << "Drawing 3 cards from the DeckCombat (which has 2 cards): \n";
    mainDeckCombat.drawCard();
    mainDeckCombat.drawCard();
    mainDeckCombat.drawCard();

    return 0;
}