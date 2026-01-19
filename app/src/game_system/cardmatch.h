#ifndef CARDMATCH_H
#define CARDMATCH_H

class Player;
class Enemy;

class CardMatch
{

public:
    CardMatch(Player &player, Enemy &enemy);

    void gainArmor(int defense);

private:
    Player &m_player;
    Enemy &m_enemy;
};

#endif