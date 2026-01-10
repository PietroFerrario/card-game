#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <string_view>


class Player{
    public: 


    Player(int hp=10): m_hp{hp}
        {}

    void setName(std::string_view name){ m_name = name;}
    std::string_view getName(){return m_name;}

    const int getHp() const {return m_hp;}

    private:
    int m_hp {};
    std::string m_name{};
};

#endif