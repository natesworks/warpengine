#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <string>
#include <memory>
#include <unordered_map>
#include <functional>

#include "../Types/Object.h"
#include "../Rendering/Drawer.h"
#include "../Types/Event.h"
#include "../Types/Vector2.h"

class Object;
class Drawer;
struct Event;

class Game
{
public:
    SDL_Renderer *renderer = nullptr;
    Vector2 scale;
    std::unique_ptr<Drawer> drawer;

    Game(int x, int y, int w, int h, std::string title = "Game", bool borderless = false);
    Game(int w, int h, std::string title = "Game", bool borderless = false);
    Game(std::string title = "Game");
    ~Game();

    template <typename T, typename... Args>
    Object *addObject(Args&&... args);
    int addEventHandler(EventType eventType, std::function<void(Event &event)> handler);
    void removeEventHandler(EventType eventType, int index);
    void start();

    int getWindowWidth();
    int getWindowHeight();
    void handleEvent(Event &event);

    bool togglableFullscreen = true;
    std::vector<Object *> objects;

private:
    SDL_Window *gameWindow = nullptr;
    int width;
    int height;

    float referenceWidth = 1920.0f;
    float referenceHeight = 1080.0f;

    void gameLoop();
    std::unordered_map<EventType, std::vector<std::function<void(Event &event)>>> eventHandlers;
};

class InitialisationFailed
{
};
class WindowCreationFailed
{
};
class RendererCreationFailed
{
};
class RenderFailed
{
};
