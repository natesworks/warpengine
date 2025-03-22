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
    void drawAll();
    void drawLine(Point start, Point end, RGB color);
    void drawRectangle(Point start, Point end, RGB color);
    void drawFilledRectangle(Point start, Point end, RGB color);
    void drawEllipse(Point center, int radiusX, int radiusY, RGB color);
    void drawFilledEllipse(Point center, int x, int y, RGB color);

private:
    Game *game;
};
