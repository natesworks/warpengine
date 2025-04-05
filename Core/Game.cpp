#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <string>
#include <iostream>
#include <thread>

#include "Game.h"
#include "../Rendering/Drawer.h"
#include "../Types/Component.h"
#include "../Types/Keys.h"

/** 
 * TODO Completly rework constructor
*/
Game::Game(int x, int y, int w, int h, std::string title, WindowType windowType) : deltaTime(0)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        throw InitialisationFailed();
    }

    uint32_t flags = 0;
    if (windowType == BORDERLESS)
    {
        flags = SDL_WINDOW_BORDERLESS;
    }
    else if (windowType == FULLSCREEN)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    else if (windowType == DESKTOPFULLSCREEN)
    {
        flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    startingWindowType = windowType;

    drawer = std::make_unique<Drawer>(this);
    gameWindow = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    if (!gameWindow)
    {
        throw WindowCreationFailed();
    }
    width = w;
    height = h;
    scale.x = w / referenceWidth;
    scale.y = h / referenceHeight;
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

int Game::addEventHandler(EventType eventType, std::function<void(Event &)> handler)
{
    eventHandlers[eventType].push_back(handler);
    return eventHandlers[eventType].size() - 1;
}

void Game::removeEventHandler(EventType eventType, int index)
{
    eventHandlers[eventType].erase(eventHandlers[eventType].begin() + index);
}

void Game::gameLoop()
{
    uint64_t now = SDL_GetPerformanceCounter();
    uint64_t last = 0;
    while (true)
    {
    eventhandler:
        last = now;
        now = SDL_GetPerformanceCounter();
        double frameTimeTicks = now - last;
        double frameTime = frameTimeTicks / (double)SDL_GetPerformanceFrequency();
        drawer->drawAll();
        deltaTime = frameTime * 1000.0;
        fps = (frameTime > 0) ? 1.0 / frameTime : 0.0f;

        SDL_Event event;
        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
        {
            exit(0);
        }
        else if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                SDL_GetWindowSize(gameWindow, &width, &height);

                SDL_Rect newViewport = {0, 0, width, height};
                SDL_RenderSetViewport(renderer, &newViewport);

                scale.x = (float)width / referenceWidth;
                scale.y = (float)height / referenceHeight;
            }
        }
        else if (event.type == SDL_KEYDOWN)
        {
            Event e;
            e.type = EventType::KEYDOWNONCE;
            e.key = (uint8_t *)SDL_GetKeyboardState(NULL);
            if (!event.key.repeat)
            {
                handleEvent(e);
                if (togglableFullscreen && event.key.keysym.sym == SDLK_F11)
                {
                    uint32_t flags = SDL_GetWindowFlags(gameWindow);
                    if (flags & SDL_WINDOW_FULLSCREEN_DESKTOP || (flags & SDL_WINDOW_FULLSCREEN_DESKTOP) == SDL_WINDOW_FULLSCREEN_DESKTOP)
                    {
                        if (startingWindowType == WINDOWED)
                        {
                            SDL_SetWindowBordered(gameWindow, SDL_TRUE);
                        }
                        else if (startingWindowType == BORDERLESS)
                        {
                            SDL_SetWindowBordered(gameWindow, SDL_FALSE);
                        }
                        SDL_SetWindowFullscreen(gameWindow, 0);
                        SDL_SetWindowResizable(gameWindow, SDL_TRUE);
                    }
                    else
                    {
                        uint32_t fullscreenType;
                        if (startingWindowType == FULLSCREEN)
                        {
                            fullscreenType = SDL_WINDOW_FULLSCREEN;
                        }
                        else
                        {
                            fullscreenType = SDL_WINDOW_FULLSCREEN_DESKTOP;
                        }
                        SDL_SetWindowFullscreen(gameWindow, fullscreenType);
                    }
                }
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            Event e;
            e.type = EventType::KEYUP;
            e.key = (uint8_t *)SDL_GetKeyboardState(NULL);
            handleEvent(e);
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            Event e;
            e.type = EventType::MOUSEBUTTONDOWN;
            e.mouseButton = event.button.button;
            e.mousePosition = Vector2(event.button.x, event.button.y);
            handleEvent(e);
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
            Event e;
            e.type = EventType::MOUSEMOTION;
            e.mousePosition.x = event.motion.x;
            e.mousePosition.y = event.motion.y;
            handleEvent(e);
        }
        else if (event.type == SDL_MOUSEWHEEL)
        {
            Event e;
            e.type = EventType::MOUSEWHEEL;
            e.mouseWheel.x = event.wheel.x;
            e.mouseWheel.y = event.wheel.y;
            handleEvent(e);
        }
        else
        {
            // fix if you press two balancing themselves out keys (W and S, A and D) at the same time and then let one go you won't move
            Event e;
            e.type = EventType::KEYDOWN;
            e.key = (uint8_t *)SDL_GetKeyboardState(NULL);
            for (int i = 0; i < 512; i++)
            {
                if (e.key[i] == 1)
                {
                    handleEvent(e);
                }
            }
        }
    }
}

void Game::start()
{
    std::thread gameLoopThread(&Game::gameLoop, this);
    gameLoopThread.detach();
}

int Game::getWindowWidth()
{
    return width;
}

int Game::getWindowHeight()
{
    return height;
}

void Game::handleEvent(Event &event)
{
    if (eventHandlers.find(event.type) != eventHandlers.end())
    {
        for (std::function<void(Event & event)> handler : eventHandlers[event.type])
        {
            handler(event);
        }
    }
    for (Object *object : objects)
    {
        for (Component *component : object->components)
        {
            component->onEvent(event);
        }
    }
}

double Game::getDeltaTime()
{
    return deltaTime;
}

double Game::getFPS()
{
    return fps;
}