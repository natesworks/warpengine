#include <SDL2/SDL.h>
#include <iostream>

#include "Drawer.h"
#include "../Types/Point.h"

void Drawer::drawLine(Point start, Point end, RGB color)
{
    /*std::cout << "[DEBUG] ScaleX: " << game->scaleX << "\n";
    std::cout << "[DEBUG] ScaleY " << game->scaleY << "\n";
    std::cout << "[DEBUG] Line Start: {" << start.x << ", " << start.y << "}\n";
    std::cout << "[DEBUG] Line End: {" << end.x << ", " << end.y << "}\n";
    std::cout << "[DEBUG] Line Color: {" << color.r << ", " << color.g << ", " << color.b << "}\n";*/

    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawLine(game->renderer, start.x * game->scaleX, start.y * game->scaleY, end.x * game->scaleX, end.y * game->scaleY);
    SDL_RenderPresent(game->renderer);

    //std::unique_ptr<Line> line = std::make_unique<Line>(start, end, color);
    //game->objects.push_back(std::move(line));
}

void Drawer::drawRectangle(Point start, Point end, RGB color)
{
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);
    SDL_Rect rect = {static_cast<int>(start.x * game->scaleX), static_cast<int>(start.y * game->scaleY), static_cast<int>((end.x - start.x) * game->scaleX), static_cast<int>((end.y - start.y) * game->scaleY)};
    SDL_RenderFillRect(game->renderer, &rect);
    SDL_RenderPresent(game->renderer);
}

void Drawer::redrawAll()
{
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    for (auto &object : game->objects)
    {
        for (auto &component : object->components)
        {
            component->draw(object.get());
        }
    }

    SDL_RenderPresent(game->renderer);
}