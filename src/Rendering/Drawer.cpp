#include <SDL2/SDL.h>
#include <iostream>

#include "Drawer.h"
#include "../Types/Point.h"

void Drawer::drawAll()
{
    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
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

void Drawer::drawLine(Point start, Point end, RGB color)
{
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawLine(game->renderer, start.x * game->scaleX, start.y * game->scaleY, end.x * game->scaleX, end.y * game->scaleY);
}

void Drawer::drawRectangle(Point start, Point end, RGB color)
{
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);
    SDL_Rect rect = {static_cast<int>(start.x * game->scaleX), static_cast<int>(start.y * game->scaleY), static_cast<int>((end.x - start.x) * game->scaleX), static_cast<int>((end.y - start.y) * game->scaleY)};
    SDL_RenderDrawRect(game->renderer, &rect);
}

void Drawer::drawFilledRectangle(Point start, Point end, RGB color)
{
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);
    SDL_Rect rect = {static_cast<int>(start.x * game->scaleX), static_cast<int>(start.y * game->scaleY), static_cast<int>((end.x - start.x) * game->scaleX), static_cast<int>((end.y - start.y) * game->scaleY)};
    SDL_RenderFillRect(game->renderer, &rect);
}

void Drawer::drawEllipse(Point center, int radiusX, int radiusY, RGB color)
{
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);
    for (int i = 0; i < 360; i++)
    {
        double angle = i * M_PI / 180;
        int x = center.x + radiusX * cos(angle) * game->scaleX;
        int y = center.y + radiusY * sin(angle) * game->scaleY;
        SDL_RenderDrawPoint(game->renderer, x, y);
    }
}

void Drawer::drawFilledEllipse(Point center, int radiusX, int radiusY, RGB color)
{
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);
    for (int i = 0; i < 360; i++)
    {
        double angle = i * M_PI / 180;
        int x = center.x + radiusX * cos(angle) * game->scaleX;
        int y = center.y + radiusY * sin(angle) * game->scaleY;
        SDL_RenderDrawPoint(game->renderer, x, y);
    }
}