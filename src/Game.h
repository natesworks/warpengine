#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <string>

class Game
{
public:
    SDL_Renderer *renderer = nullptr;

    Game(int x, int y, int w, int h, std::string title = "Game", bool borderless = false);
    Game(int w, int h, std::string title = "Game", bool borderless = false);
    Game(std::string title = "Game");
    ~Game();

    void handleEvents();

private:
    SDL_Window *gameWindow = nullptr;
};

class InitialisationFailed {};
class WindowCreationFailed {};
class RendererCreationFailed {};
class RenderFailure {};