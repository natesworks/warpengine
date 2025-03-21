#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <string>
#include <memory>

#include "Types/Object.h"
#include "Rendering/Drawer.h"

class Object;
class Drawer;

class Game
{
public:
    SDL_Renderer *renderer = nullptr;
    float scaleX;
    float scaleY;
    std::vector<std::unique_ptr<Object>> objects;
    std::unique_ptr<Drawer> drawer;

    Game(int x, int y, int w, int h, std::string title = "Game", bool borderless = false);
    Game(int w, int h, std::string title = "Game", bool borderless = false);
    Game(std::string title = "Game");
    ~Game();

    void handleEvents();
    void addObject(Object);
    Object& getObject(int index);

private:
    SDL_Window *gameWindow = nullptr;
    int originalWidth;
    int originalHeight;
};

class InitialisationFailed {};
class WindowCreationFailed {};
class RendererCreationFailed {};
class RenderFailed {};
