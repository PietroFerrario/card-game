#include <iostream>

#include "game_system/game.h"
#include "game_system/iotext.h"


int main(){

    IOText io{std::cout, std::cin};
    Game game{io};

    game.intro();

    //while(!game.isLost()){
    //}

    game.lossMessage();

    return 0;
}