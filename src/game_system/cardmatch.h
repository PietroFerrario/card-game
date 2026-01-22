#ifndef CARDMATCH_H
#define CARDMATCH_H

#include "deck/deckCombat.h"
#include "factories/cardFactory.h"

class Player;
class Enemy;

class CardMatch
{

  public:
    CardMatch(Player& player, Enemy& enemy);

    void drawMultipleCards(int amount);
    void playCard(int handIndex);

    void gainArmor(int defense);

  private:
    Player& m_player;
    Enemy& m_enemy;

    CardFactory m_cardFactory;

    DeckCombat m_deckCombat;
};

#endif