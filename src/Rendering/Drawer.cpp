#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

#include "Drawer.h"
#include "../Types/Vector2.h"

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

void Drawer::drawLine(Vector2 start, Vector2 end, RGB color, float rotation)
{
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);

    float centerX = (start.x + end.x) / 2.0f;
    float centerY = (start.y + end.y) / 2.0f;

    float translatedStartX = start.x - centerX;
    float translatedStartY = start.y - centerY;
    float translatedEndX = end.x - centerX;
    float translatedEndY = end.y - centerY;

    float rotatedStartX = translatedStartX * cos(rotation) - translatedStartY * sin(rotation);
    float rotatedStartY = translatedStartX * sin(rotation) + translatedStartY * cos(rotation);
    float rotatedEndX = translatedEndX * cos(rotation) - translatedEndY * sin(rotation);
    float rotatedEndY = translatedEndX * sin(rotation) + translatedEndY * cos(rotation);

    rotatedStartX += centerX;
    rotatedStartY += centerY;
    rotatedEndX += centerX;
    rotatedEndY += centerY;

    SDL_RenderDrawLine(game->renderer, rotatedStartX * game->scaleX, rotatedStartY * game->scaleY, rotatedEndX * game->scaleX, rotatedEndY * game->scaleY);
}

void Drawer::drawRectangle(Vector2 start, Vector2 end, RGB color, float rotation)
{
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);

    float centerX = (start.x + end.x) / 2.0f;
    float centerY = (start.y + end.y) / 2.0f;

    Vector2 corners[4] = {
        {start.x, start.y},
        {end.x, start.y},
        {end.x, end.y},
        {start.x, end.y}
    };

    for (int i = 0; i < 4; ++i)
    {
        float translatedX = corners[i].x - centerX;
        float translatedY = corners[i].y - centerY;

        float rotatedX = translatedX * cos(rotation) - translatedY * sin(rotation);
        float rotatedY = translatedX * sin(rotation) + translatedY * cos(rotation);

        corners[i].x = rotatedX + centerX;
        corners[i].y = rotatedY + centerY;
    }

    SDL_RenderDrawLine(game->renderer, corners[0].x * game->scaleX, corners[0].y * game->scaleY, corners[1].x * game->scaleX, corners[1].y * game->scaleY);
    SDL_RenderDrawLine(game->renderer, corners[1].x * game->scaleX, corners[1].y * game->scaleY, corners[2].x * game->scaleX, corners[2].y * game->scaleY);
    SDL_RenderDrawLine(game->renderer, corners[2].x * game->scaleX, corners[2].y * game->scaleY, corners[3].x * game->scaleX, corners[3].y * game->scaleY);
    SDL_RenderDrawLine(game->renderer, corners[3].x * game->scaleX, corners[3].y * game->scaleY, corners[0].x * game->scaleX, corners[0].y * game->scaleY);
}

void Drawer::drawFilledRectangle(Vector2 start, Vector2 end, RGB color, float rotation)
{
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);

    float centerX = (start.x + end.x) / 2.0f;
    float centerY = (start.y + end.y) / 2.0f;

    Vector2 corners[4] = 
    {
        {start.x, start.y},
        {end.x, start.y},
        {end.x, end.y},
        {start.x, end.y}
    };

    for (int i = 0; i < 4; ++i)
    {
        float translatedX = corners[i].x - centerX;
        float translatedY = corners[i].y - centerY;

        float rotatedX = translatedX * cos(rotation) - translatedY * sin(rotation);
        float rotatedY = translatedX * sin(rotation) + translatedY * cos(rotation);

        corners[i].x = rotatedX + centerX;
        corners[i].y = rotatedY + centerY;
    }

    SDL_Vertex verts[4];
    for (int i = 0; i < 4; ++i)
    {
        verts[i].position.x = corners[i].x * game->scaleX;
        verts[i].position.y = corners[i].y * game->scaleY;
        verts[i].color = {color.r, color.g, color.b, 255};
    }

    int indices[] = {0, 1, 2, 2, 3, 0};
    SDL_RenderGeometry(game->renderer, nullptr, verts, 4, indices, 6);
}

void Drawer::drawEllipse(Vector2 center, float radiusX, float radiusY, RGB color, float rotation)
{
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);
    for (int i = 0; i < 360; i++)
    {
        double angle = i * M_PI / 180;
        float x = radiusX * cos(angle);
        float y = radiusY * sin(angle);

        float translatedX = x * game->scaleX;
        float translatedY = y * game->scaleY;

        float rotatedX = translatedX * cos(rotation) - translatedY * sin(rotation);
        float rotatedY = translatedX * sin(rotation) + translatedY * cos(rotation);

        SDL_RenderDrawPoint(game->renderer, center.x * game->scaleX + rotatedX, center.y * game->scaleY + rotatedY);
    }
}

void Drawer::drawFilledEllipse(Vector2 center, int radiusX, int radiusY, RGB color, float rotation)
{
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);
    for (int y = -radiusY; y <= radiusY; y++)
    {
        for (int x = -radiusX; x <= radiusX; x++)
        {
            if ((x * x * radiusY * radiusY + y * y * radiusX * radiusX) <= (radiusX * radiusX * radiusY * radiusY))
            {
                float translatedX = x * game->scaleX;
                float translatedY = y * game->scaleY;

                float rotatedX = translatedX * cos(rotation) - translatedY * sin(rotation);
                float rotatedY = translatedX * sin(rotation) + translatedY * cos(rotation);

                SDL_RenderDrawPoint(game->renderer, center.x * game->scaleX + rotatedX, center.y * game->scaleY + rotatedY);
            }
        }
    }
}