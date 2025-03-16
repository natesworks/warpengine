#include <SDL2/SDL.h>
#include <iostream>

#include "Drawer.h"

void Drawer::drawLine(int x1, int y1, int x2, int y2, RGB color)
{
    std::cout << "[DEBUG] ScaleX " << game->scaleX << "\n[DEBUG] ScaleY " << game->scaleY << "\n";
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawLine(game->renderer, x1 * game->scaleX, y1 * game->scaleY, x2 * game->scaleX, y2 * game->scaleY);
    SDL_RenderPresent(game->renderer);
}
