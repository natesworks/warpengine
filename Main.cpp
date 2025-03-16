#include <iostream>

#include "src/Game.h"

int main()
{
    Game game = Game(800, 600);
    while (true)
    {
        game.handleEvents();
    }
    return 0;
}