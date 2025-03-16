#pragma once

#include <SDL2/SDL.h>

#include "../RGB.h"
#include "../Game.h"
#include "../Point.h"

class Drawer
{
public:
    Drawer(Game *game) : game(game) {};
    void drawLine(Point start, Point end, RGB color);

private:
    Game *game;
};
