#pragma once

#include <SDL2/SDL.h>

#include "../Types/RGB.h"
#include "../Game.h"
#include "../Types/Point.h"

class Game;

class Drawer
{
public:
    Drawer(Game *game) : game(game) {};
    void drawLine(Point start, Point end, RGB color);
    void drawRectangle(Point start, Point end, RGB color);
    //void drawCircle(Point center, int radius, RGB color);

private:
    Game *game;
};
