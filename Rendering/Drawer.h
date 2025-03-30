#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "../Types/RGB.h"
#include "../Core/Game.h"
#include "../Types/Vector2.h"

class Game;

class Drawer
{
public:
    Drawer(Game *game) : game(game) {};
    void drawAll();
    void drawLine(Vector2 start, Vector2 end, RGB color, float rotation = 0);
    void drawRectangle(Vector2 start, Vector2 end, RGB color, float rotation = 0);
    void drawFilledRectangle(Vector2 start, Vector2 end, RGB color, float rotation = 0);
    void drawEllipse(Vector2 center, float radiusX, float radiusY, RGB color, float rotation = 0);
    void drawFilledEllipse(Vector2 center, float radiusX, float radiusY, RGB color, float rotation = 0);
    void drawText(std::string text, std::string font, int fontSize, Vector2 position, Vector2 scale, RGB color);

private:
    Game *game;
};
