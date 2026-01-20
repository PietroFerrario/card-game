#include "deck/deckPlayer.h"
#include "deck/deckEntry.h"

#include <vector>
#include <iostream>

int main()
{
    std::vector<DeckEntry> initialCardList{{"archer", 2}, {"warrior", 3}, {"shieldMaiden", 1}};

    DeckPlayer mainDeck{initialCardList};

    std::cout << mainDeck;

    std::cout << "Current card in the deck: " << mainDeck.getCurrentCardNumber() << "\n";

    mainDeck.addCard("shieldMaiden");

    std::cout << mainDeck << "\n";

    mainDeck.addCard("duelist");

    std::cout << mainDeck << "\n";

    std::cout << "Current card in the deck: " << mainDeck.getCurrentCardNumber() << "\n";

    mainDeck.removeCard("duelist");

    std::cout << mainDeck << "\n";

    std::cout << "Current card in the deck: " << mainDeck.getCurrentCardNumber() << "\n";

    mainDeck.removeCard("duelist");

    std::cout << mainDeck << "\n";

    std::cout << "Current card in the deck: " << mainDeck.getCurrentCardNumber() << "\n";

    return 0;
}