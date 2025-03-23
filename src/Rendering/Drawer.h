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
    void drawLine(Point start, Point end, RGB color, float rotation = 0);
    void drawRectangle(Point start, Point end, RGB color, float rotation = 0);
    void drawFilledRectangle(Point start, Point end, RGB color, float rotation = 0);
    void drawEllipse(Point center, float radiusX, float radiusY, RGB color, float rotation = 0);
    void drawFilledEllipse(Point center, int x, int y, RGB color, float rotation = 0);

private:
    Game *game;
};
