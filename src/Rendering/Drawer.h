#pragma once

#include <SDL2/SDL.h>

#include "../RGB.h"
#include "../Game.h"

class Drawer
{
public:
    Drawer(Game *game) : game(game) {};
    void drawLine(int x1, int y1, int x2, int y2, RGB color);

private:
    Game *game;
};
