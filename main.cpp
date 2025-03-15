#include <iostream>

#include "src/warpengine.h"

int main()
{
    try
    {
        Game game;
    }
    catch (InitialisationFailed)
    {
        std::cout << "Failed to initialise engine...\n";
    }
    std::cout << "Press any key to exit...\n";
    std::cin.get();
    return 0;
}