#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <string.h>
#include <iostream>

#include "Game.h"

Game::Game(int x, int y, int w, int h, std::string title, bool borderless)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        throw InitialisationFailed();
    }

    uint32_t flags = 0;
    if (borderless)
    {
        flags = SDL_WINDOW_BORDERLESS;
    }

    gameWindow = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    if (!gameWindow)
    {
        throw WindowCreationFailed();
    }
    originalWidth = w;
    originalHeight = h;
    scaleX = w / 1001.0f ;
    scaleY = w / 1001.0f;
    SDL_SetWindowResizable(gameWindow, SDL_TRUE);
    renderer = SDL_CreateRenderer(gameWindow, -1, 0);

    if (!renderer)
    {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        throw RendererCreationFailed();
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    if (SDL_RenderClear(renderer) != 0)
    {
        throw RenderFailed();
    }
    SDL_RenderPresent(renderer);
}

Game::Game(int w, int h, std::string title, bool borderless) : Game(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, title, borderless) {}

Game::Game(std::string title)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        throw InitialisationFailed();
    }

    gameWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!gameWindow)
    {
        throw WindowCreationFailed();
    }
    SDL_DisplayMode displayMode;
    if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0)
    {
        throw WindowCreationFailed();
    }
    originalWidth = displayMode.w;
    originalHeight = displayMode.h;
    scaleX = displayMode.w / 1920.0f;
    scaleY = displayMode.h / 1080.0f;
    SDL_SetWindowResizable(gameWindow, SDL_TRUE);
    renderer = SDL_CreateRenderer(gameWindow, -1, 0);
    if (!renderer)
    {
        throw RendererCreationFailed();
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    if (SDL_RenderClear(renderer) != 0)
    {
        throw RenderFailed();
    }
    SDL_RenderPresent(renderer);
}

Game::~Game()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (gameWindow)
    {
        SDL_DestroyWindow(gameWindow);
    }
    SDL_Quit();
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_WaitEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        exit(0);
        break;
    case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            std::cout << "[DEBUG] Window has been resized.";
            int newWidth, newHeight;
            SDL_GetWindowSize(gameWindow, &newWidth, &newHeight);

            SDL_Rect newViewport = {0, 0, newWidth, newHeight};
            SDL_RenderSetViewport(renderer, &newViewport);

            scaleX = (float)newWidth / originalWidth;
            scaleY = (float)newHeight / originalHeight;

            break;
        }
    }
}
