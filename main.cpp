#include <iostream>

#include "src/Game.h"

int main()
{
    Game game(800, 600);
    std::cout << "Press any key to exit...\n";
    std::cin.get();
    return 0;
}