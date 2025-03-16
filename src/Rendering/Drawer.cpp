#include "Drawer.h"

void Drawer::drawLine(int x1, int y1, int x2, int y2, RGB color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_RenderPresent(renderer);
}
