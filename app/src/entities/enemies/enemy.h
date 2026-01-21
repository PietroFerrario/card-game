#ifndef ENEMY_H
#define ENEMY_H

class Enemy
{
public:
    Enemy(int hp, int attack);

    int getHp() const { return m_hp; }
    int getAttack() const { return m_attack; }

    void takeDamage(int amount);
    void heal(int amount);

private:
    int m_hp{};
    int m_attack{};
};

#endif // ENEMY_H