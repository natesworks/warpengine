#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <string>
#include <memory>
#include <unordered_map>
#include <functional>

#include "Types/Object.h"
#include "Rendering/Drawer.h"
#include "Types/Event.h"

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

    void addObject(Object);
    Object* getObject(int index);

    void setEventHandler(EventType eventType, std::function<void(Event& event)> handler);
    void start();

    int getWindowWidth();
    int getWindowHeight();

private:
    std::unordered_map<EventType, std::function<void(Event& event)>> eventHandlers;
    SDL_Window *gameWindow = nullptr;
    int originalWidth;
    int originalHeight;
    int width;
    int height;

    void handleEvents();
    void gameLoop();
};

class InitialisationFailed {};
class WindowCreationFailed {};
class RendererCreationFailed {};
class RenderFailed {};
