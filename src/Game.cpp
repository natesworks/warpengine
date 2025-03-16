#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <string.h>

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
    renderer = SDL_CreateRenderer(gameWindow, -1, 0);
    if (!renderer)
    {
        throw RendererCreationFailed();
    }
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    //SDL_RenderClear(renderer); 
    //SDL_RenderPresent(renderer);
}

Game::Game(int w, int h, std::string title, bool borderless)
{
    Game(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, title, borderless);
}

Game::Game(std::string title)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        throw InitialisationFailed();
    }

    gameWindow = SDL_CreateWindow(title.c_str(), 0, 0, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    renderer = SDL_CreateRenderer(gameWindow, -1, 0);
    if (!gameWindow)
    {
        throw WindowCreationFailed();
    }
    renderer = SDL_CreateRenderer(gameWindow, -1, 0);
    if (!renderer)
    {
        throw RendererCreationFailed();
    }
}

Game::~Game()
{
    SDL_DestroyWindow(gameWindow);
    SDL_DestroyRenderer(renderer);
}