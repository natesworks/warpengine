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
#include "Types/Vector2.h"

class Object;
class Drawer;

class Game
{
public:
    SDL_Renderer *renderer = nullptr;
    Vector2 scale;
    std::vector<std::unique_ptr<Object>> objects;
    std::unique_ptr<Drawer> drawer;

    Game(int x, int y, int w, int h, std::string title = "Game", bool borderless = false);
    Game(int w, int h, std::string title = "Game", bool borderless = false);
    Game(std::string title = "Game");
    ~Game();

    void addObject(Object);
    Object* getObject(int index);

    int addEventHandler(EventType eventType, std::function<void(Event& event)> handler);
    void removeEventHandler(EventType eventType, int index);
    void start();

    int getWindowWidth();
    int getWindowHeight();

    bool togglableFullscreen = true;

private:
    std::unordered_map<EventType, std::vector<std::function<void(Event& event)>>> eventHandlers;
    SDL_Window *gameWindow = nullptr;
    int width;
    int height;

    float referenceWidth = 1920.0f;
    float referenceHeight = 1080.0f;

    void handleEvents();
    void gameLoop();
};;

class InitialisationFailed {};
class WindowCreationFailed {};
class RendererCreationFailed {};
class RenderFailed {};
