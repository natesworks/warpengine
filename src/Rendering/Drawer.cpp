#include <SDL2/SDL.h>
#include <iostream>

#include "Drawer.h"
#include "../Point.h"

void Drawer::drawLine(Point start, Point end, RGB color)
{
    std::cout << "[DEBUG] ScaleX " << game->scaleX << "\n[DEBUG] ScaleY " << game->scaleY << "\n";
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawLine(game->renderer, start.x * game->scaleX, start.y * game->scaleY, end.x * game->scaleX, end.y * game->scaleY);
    SDL_RenderPresent(game->renderer);
}
