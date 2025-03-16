#include <SDL2/SDL.h>
#include <iostream>

#include "Drawer.h"
#include "../Point.h"
#include "../Objects/Line.h"

void Drawer::drawLine(Point start, Point end, RGB color)
{
    if (!game)
    {
        std::cerr << "Game is not initialized!\n";
        return;
    }

    std::cout << "[DEBUG] ScaleX: " << game->scaleX << "\n";
    std::cout << "[DEBUG] ScaleY " << game->scaleY << "\n";
    std::cout << "[DEBUG] Line Start: {" << start.x << ", " << start.y << "}\n";
    std::cout << "[DEBUG] Line End: {" << end.x << ", " << end.y << "}\n";
    std::cout << "[DEBUG] Line Color: {" << color.r << ", " << color.g << ", " << color.b << "}\n";

    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawLine(game->renderer, start.x * game->scaleX, start.y * game->scaleY, end.x * game->scaleX, end.y * game->scaleY);
    SDL_RenderPresent(game->renderer);

    std::unique_ptr<Line> line = std::make_unique<Line>(start, end, color);
    game->objects.push_back(std::move(line));
}
