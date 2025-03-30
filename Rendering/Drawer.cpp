#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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
            component->draw(object);
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

    SDL_RenderDrawLine(game->renderer, rotatedStartX * game->scale.x, rotatedStartY * game->scale.y, rotatedEndX * game->scale.x, rotatedEndY * game->scale.y);
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

    SDL_RenderDrawLine(game->renderer, corners[0].x * game->scale.x, corners[0].y * game->scale.y, corners[1].x * game->scale.x, corners[1].y * game->scale.y);
    SDL_RenderDrawLine(game->renderer, corners[1].x * game->scale.x, corners[1].y * game->scale.y, corners[2].x * game->scale.x, corners[2].y * game->scale.y);
    SDL_RenderDrawLine(game->renderer, corners[2].x * game->scale.x, corners[2].y * game->scale.y, corners[3].x * game->scale.x, corners[3].y * game->scale.y);
    SDL_RenderDrawLine(game->renderer, corners[3].x * game->scale.x, corners[3].y * game->scale.y, corners[0].x * game->scale.x, corners[0].y * game->scale.y);
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
        verts[i].position.x = corners[i].x * game->scale.x;
        verts[i].position.y = corners[i].y * game->scale.y;
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
        double angle = i * M_PI / 180.0;
        float cosRotation = cos(rotation);
        float sinRotation = sin(rotation);

        float x = radiusX * cosRotation * game->scale.x;
        float y = radiusY * sinRotation * game->scale.y;

        float translatedX = x * game->scale.x;
        float translatedY = y * game->scale.y;

        float rotatedX = translatedX * cosRotation - translatedY * sinRotation;
        float rotatedY = translatedX * sinRotation + translatedY * cosRotation;

        SDL_RenderDrawPoint(game->renderer, center.x * game->scale.x + rotatedX, center.y * game->scale.y + rotatedY);
    }
}

void Drawer::drawFilledEllipse(Vector2 center, float radiusX, float radiusY, RGB color, float rotation)
{
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);
    for (int y = -radiusY; y <= radiusY; y++)
    {
        for (int x = -radiusX; x <= radiusX; x++)
        {
            if ((x * x * radiusY * radiusY + y * y * radiusX * radiusX) <= (radiusX * radiusX * radiusY * radiusY))
            {
                float translatedX = x * game->scale.x;
                float translatedY = y * game->scale.y;

                float cosRotation = cos(rotation);
                float sinRotation = sin(rotation);

                float rotatedX = translatedX * cosRotation - translatedY * sinRotation;
                float rotatedY = translatedX * sinRotation + translatedY * cosRotation;

                SDL_RenderDrawPoint(game->renderer, center.x * game->scale.x + rotatedX, center.y * game->scale.y + rotatedY);
            }
        }
    }
}

void Drawer::drawText(std::string text, std::string fontPath, int fontSize, Vector2 position, Vector2 scale, RGB rgb)
{
    TTF_Init();
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (font == NULL)
    {
        std::cerr << "Failed to open font\n";
        std::cerr << SDL_GetError() << "\n";
        exit(1);
    }

    SDL_Color color = {rgb.r, rgb.g, rgb.b};
    SDL_Surface *messageSurface = TTF_RenderText_Solid(font, text.c_str(), color); 
    SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(game->renderer, messageSurface);
    SDL_Rect messageRect;

    messageRect.x = position.x;
    messageRect.y = position.y;
    messageRect.w = scale.x;
    messageRect.h = scale.y;

    SDL_RenderCopy(game->renderer, messageTexture, NULL, &messageRect);
    SDL_FreeSurface(messageSurface);
    SDL_DestroyTexture(messageTexture);
    TTF_CloseFont(font);
}