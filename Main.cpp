#include <iostream>

#include "src/Game.h"
#include "src/Rendering/Drawer.h"

int main()
{
    Game game = Game(800, 600);
    Drawer drawer(game.renderer);
    drawer.drawLine(0, 0, 100, 100, RGB(255, 0, 0));
    while (true)
    {
        game.handleEvents();
    }
    return 0;
}