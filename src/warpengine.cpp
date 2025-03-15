#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#include "warpengine.h"

Game::Game(int x, int y, int w, int h, std::string title)
{
    SDL_Init(SDL_INIT_VIDEO);
    gameWindow = SDL_CreateWindow(title.c_str(), x, y, w, h, 0);
}

Game::Game(std::string title)
{
    SDL_Init(SDL_INIT_VIDEO);
    gameWindow = SDL_CreateWindow(title.c_str(), 0, 0, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
}