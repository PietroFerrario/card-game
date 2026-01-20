#include "card_system/cardMaker.h"
#include "card_system/card.h"

int main()
{
    CardMaker cardMaker;

    Card shieldWarrior = cardMaker.makeSingleCard("shieldWarrior");

    return 0;
}