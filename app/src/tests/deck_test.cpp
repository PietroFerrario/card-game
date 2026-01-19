#include "card_system/deckPlayer.h"
#include "card_system/deckEntry.h"

#include <vector>
#include <iostream>

int main()
{
    std::vector<DeckEntry> initial_card_list{{"archer", 2}, {"warrior", 3}, {"shieldMaiden", 1}};

    DeckPlayer main_deck{initial_card_list};

    std::cout << main_deck;

    std::cout << "Current card in the deck: " << main_deck.getCurrentCardNumber() << "\n";

    main_deck.addCard("shieldMaiden");

    std::cout << main_deck << "\n";

    main_deck.addCard("duelist");

    std::cout << main_deck << "\n";

    std::cout << "Current card in the deck: " << main_deck.getCurrentCardNumber() << "\n";

    main_deck.removeCard("duelist");

    std::cout << main_deck << "\n";

    std::cout << "Current card in the deck: " << main_deck.getCurrentCardNumber() << "\n";

    main_deck.removeCard("duelist");

    std::cout << main_deck << "\n";

    std::cout << "Current card in the deck: " << main_deck.getCurrentCardNumber() << "\n";

    return 0;
}