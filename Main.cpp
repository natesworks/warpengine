#include <iostream>

#include "src/Game.h"
#include "src/Rendering/Drawer.h"

int main()
{
    Game game = Game(500, 500);
    Drawer drawer(&game);
    drawer.drawLine(0, 1000, 500, 1000, RGB(255, 0, 0));
    while (true)
    {
        game.handleEvents();
    }
    return 0;
}