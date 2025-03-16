#include <iostream>

#include "src/game.h"

int main()
{
    try
    {
        Game game(800, 600, "Game");
    }
    catch (InitialisationFailed)
    {
        std::cout << "Failed to initialise engine...\n";
    }
    std::cout << "Press any key to exit...\n";
    std::cin.get();
    return 0;
}