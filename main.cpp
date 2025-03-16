#include <iostream>

#include "src/Game.h"

Game game;

int main()
{
    game = Game(800, 600);
    std::cout << "Press any key to exit...\n";
    std::cin.get();
    return 0;
}