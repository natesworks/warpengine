#pragma once

#include <SDL2/SDL.h>
#include "../RGB.h"

class Drawer
{
public:
    Drawer(SDL_Renderer *renderer) : renderer(renderer) {};
    void drawLine(int x1, int y1, int x2, int y2, RGB color);

private:
    SDL_Renderer *renderer;
};
