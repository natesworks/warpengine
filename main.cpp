#include <iostream>

#include "src/warpengine.h"

int main()
{
    try
    {
        Game game(800, 600, "Game", true);
    }
    catch (InitialisationFailed)
    {
        std::cout << "Failed to initialise engine...\n";
    }
    std::cout << "Press any key to exit...\n";
    std::cin.get();
    return 0;
}