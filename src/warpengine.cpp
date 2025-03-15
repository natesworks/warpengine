#include <SDL2/SDL.h>
#include <string.h>

#include "warpengine.h"

Game::Game(int x, int y, int w, int h, std::string title)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        throw InitialisationFailed();
    }

    gameWindow = SDL_CreateWindow(title.c_str(), x, y, w, h, 0);
}

Game::Game(int w, int h, std::string title)
{
    Game(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, title);
}

Game::Game(std::string title)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        throw InitialisationFailed();
    }

    gameWindow = SDL_CreateWindow(title.c_str(), 0, 0, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
}