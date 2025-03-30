#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <asm-generic/errno.h>
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
    start.x = start.x * game->scale.x;
    start.y = start.y * game->scale.y;
    end.x = end.x * game->scale.x;
    end.y = end.y * game->scale.y;

    Vector2 center = {(start.x + end.x) * 0.5f, (start.y + end.y) * 0.5f};

    start = {
        (start.x - center.x) * cos(rotation) - (start.y - center.y) * sin(rotation) + center.x,
        (start.x - center.x) * sin(rotation) + (start.y - center.y) * cos(rotation) + center.y};

    end = {
        (end.x - center.x) * cos(rotation) - (end.y - center.y) * sin(rotation) + center.x,
        (end.x - center.x) * sin(rotation) + (end.y - center.y) * cos(rotation) + center.y};

    SDL_RenderDrawLine(game->renderer, start.x, start.y, end.x, end.y);
}

void Drawer::drawRectangle(Vector2 start, Vector2 end, RGB color, float rotation)
{
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);

    float centerX = (start.x + end.x) * game->scale.x;
    float centerY = (start.y + end.y) * game->scale.y;

    Vector2 corners[4] = {
        {start.x, start.y},
        {end.x, start.y},
        {end.x, end.y},
        {start.x, end.y}};

    for (int i = 0; i < 4; ++i)
    {
        float translatedX = corners[i].x - centerX;
        float translatedY = corners[i].y - centerY;

        float rotatedX = translatedX * cos(rotation) - translatedY * sin(rotation);
        float rotatedY = translatedX * sin(rotation) + translatedY * cos(rotation);

        corners[i].x = rotatedX + centerX;
        corners[i].y = rotatedY + centerY;
    }

    drawLine(corners[0], corners[1], color, 0);
    drawLine(corners[1], corners[2], color, 0);
    drawLine(corners[2], corners[3], color, 0);
    drawLine(corners[3], corners[0], color, 0);
}

void Drawer::drawFilledRectangle(Vector2 start, Vector2 end, RGB color, float rotation)
{
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);

    float centerX = (start.x + end.x) * game->scale.x;
    float centerY = (start.y + end.y) * game->scale.y;

    Vector2 corners[4] =
        {
            {start.x, start.y},
            {end.x, start.y},
            {end.x, end.y},
            {start.x, end.y}};

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

void Drawer::drawEllipse(Vector2 center, Vector2 radius, RGB color, float rotation)
{
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);
    radius.x = radius.x * game->scale.x;
    radius.y = radius.y * game->scale.y;
    center.x = center.x * game->scale.x;
    center.y = center.y * game->scale.y;
    for (int i = 0; i < 360; i++)
    {
        double angle = i * M_PI / 180.0;
        float cosRotation = cos(rotation);
        float sinRotation = sin(rotation);

        float x = (radius.x * cosRotation * game->scale.x);
        float y = (radius.y * sinRotation * game->scale.y);

        x = x * cosRotation - y * sinRotation;
        y = x * sinRotation + y * cosRotation;

        SDL_RenderDrawPoint(game->renderer, center.x + x, center.y + y);
    }
}

void Drawer::drawFilledEllipse(Vector2 center, Vector2 radius, RGB color, float rotation)
{
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);
    radius.x = radius.x * game->scale.x;
    radius.y = radius.y * game->scale.y;
    center.x = center.x * game->scale.x;
    center.y = center.y * game->scale.y;
    for (int y = -radius.y; y <= radius.y; y++)
    {
        for (int x = -radius.x; x <= radius.x; x++)
        {
            if ((x * x * radius.y * radius.y + y * y * radius.x * radius.x) <= (radius.x * radius.x * radius.y * radius.y))
            {
                float translatedX = x;
                float translatedY = y;

                float cosRotation = cos(rotation);
                float sinRotation = sin(rotation);

                float rotatedX = translatedX * cosRotation - translatedY * sinRotation;
                float rotatedY = translatedX * sinRotation + translatedY * cosRotation;

                SDL_RenderDrawPoint(game->renderer, center.x + rotatedX, center.y + rotatedY);
            }
        }
    }
}

void Drawer::drawText(std::string text, std::string fontPath, int fontSize, Vector2 position, Vector2 scale, RGB rgb, float rotation)
{
    TTF_Init();
    TTF_Font *font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (font == NULL)
    {
        std::cerr << "Failed to open font\n";
        std::cerr << SDL_GetError() << "\n";
        exit(1);
    }

    SDL_Color color = {rgb.r, rgb.g, rgb.b};
    SDL_Surface *messageSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *messageTexture = SDL_CreateTextureFromSurface(game->renderer, messageSurface);
    SDL_Rect messageRect;

    messageRect.x = position.x * game->scale.x;
    messageRect.y = position.y * game->scale.y;
    messageRect.w = scale.x * game->scale.x;
    messageRect.h = scale.y * game->scale.y;

    SDL_RenderCopy(game->renderer, messageTexture, NULL, &messageRect);
    SDL_FreeSurface(messageSurface);
    SDL_DestroyTexture(messageTexture);
    TTF_CloseFont(font);
}

void Drawer::drawSprite(std::string imagePath, Vector2 position, Vector2 scale, RGB rgb, float rotation)
{
    IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG || IMG_INIT_AVIF || IMG_INIT_JXL || IMG_INIT_TIF);
    SDL_Surface *surface = IMG_Load(imagePath.c_str());
    SDL_Texture *tex = SDL_CreateTextureFromSurface(game->renderer, surface);

    SDL_Rect rect;
    rect.x = position.x * game->scale.x;
    rect.y = position.y * game->scale.y;
    rect.w = scale.x * game->scale.x;
    rect.h = scale.x * game->scale.y;

    SDL_RenderCopy(game->renderer, tex, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(tex);
}

void Drawer::drawTriangle(Vector2 position, Vector2 scale, RGB color, float rotation)
{
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);

    position.x = position.x * game->scale.x;
    position.y = position.y * game->scale.y;
    scale.x = scale.x * game->scale.x;
    scale.y = scale.y * game->scale.y;

    Vector2 vertices[3] = {
        {position.x, position.y - scale.y},
        {position.x - scale.x, position.y + scale.y},
        {position.x + scale.x, position.y + scale.y}};

    for (int i = 0; i < 3; ++i)
    {
        float translatedX = vertices[i].x - position.x;
        float translatedY = vertices[i].y - position.y;

        float rotatedX = translatedX * cos(rotation) - translatedY * sin(rotation);
        float rotatedY = translatedX * sin(rotation) + translatedY * cos(rotation);

        vertices[i].x = rotatedX + position.x;
        vertices[i].y = rotatedY + position.y;
    }

    SDL_RenderDrawLine(game->renderer, vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y);
    SDL_RenderDrawLine(game->renderer, vertices[1].x, vertices[1].y, vertices[2].x, vertices[2].y);
    SDL_RenderDrawLine(game->renderer, vertices[2].x, vertices[2].y, vertices[0].x, vertices[0].y);
}

void Drawer::drawFilledTriangle(Vector2 position, Vector2 scale, RGB color, float rotation)
{
    SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);
    position.x = position.x * game->scale.x;
    position.y = position.y * game->scale.y;
    scale.x = scale.x * game->scale.x;
    scale.y = scale.y * game->scale.y;

    Vector2 vertices[3] = {
        {position.x, position.y - scale.y},
        {position.x - scale.x, position.y + scale.y},
        {position.x + scale.x, position.y + scale.y}};

    SDL_Vertex verts[3];
    for (int i = 0; i < 3; ++i)
    {
        verts[i].position.x = vertices[i].x;
        verts[i].position.y = vertices[i].y;
        verts[i].color = {color.r, color.g, color.b, 255};
    }

    int indices[] = {0, 1, 2};
    SDL_RenderGeometry(game->renderer, nullptr, verts, 3, indices, 3);
}