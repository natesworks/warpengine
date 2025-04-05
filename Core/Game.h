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
#include "../Types/WindowType.h"
#include "../Types/WindowType.h"
#include "../Types/WindowSettings.h"

class Object;
class Drawer;
struct Event;

class Game
{
public:
    SDL_Renderer *renderer = nullptr;
    Vector2 scale;
    Drawer *drawer;


    template <typename... Args>
    Game(Args &&...args) : windowSettings(std::forward<Args>(args)...) {}
    ~Game();

    template <typename... Args>
    Object *addObject(Args &&...args)
    {
        Object *object = new Object(this, std::forward<Args>(args)...);
        objects.push_back(object);
        return object;
    }
    int addEventHandler(EventType eventType, std::function<void(Event &event)> handler);
    void removeEventHandler(EventType eventType, int index);
    void start();

    int getWindowWidth();
    int getWindowHeight();
    double getDeltaTime();
    double getFPS();

    void handleEvent(Event &event);

    bool togglableFullscreen = true;
    std::vector<Object *> objects;
    WindowSettings windowSettings;

private:
    SDL_Window *gameWindow = nullptr;

    double deltaTime;
    double fps;

    void gameLoop();
    std::unordered_map<EventType, std::vector<std::function<void(Event &event)>>> eventHandlers;
    WindowType startingWindowType;
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
