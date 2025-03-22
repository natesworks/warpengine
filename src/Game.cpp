#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <string.h>
#include <iostream>

#include "Game.h"
#include "Rendering/Drawer.h"
#include "Enums/Keys.h"

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

    drawer = std::make_unique<Drawer>(this);
    gameWindow = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    if (!gameWindow)
    {
        throw WindowCreationFailed();
    }
    originalWidth = w;
    originalHeight = h;
    width = w;
    height = h;
    scaleX = w / 1000.1f;
    scaleY = w / 1000.1f;
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

Game::Game(int w, int h, std::string title, bool borderless) : Game(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, title, borderless) {}

Game::Game(std::string title)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        throw InitialisationFailed();
    }

    drawer = std::make_unique<Drawer>(this);
    gameWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!gameWindow)
    {
        throw WindowCreationFailed();
    }
    SDL_DisplayMode displayMode;
    if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0)
    {
        throw WindowCreationFailed();
    }
    originalWidth = displayMode.w;
    originalHeight = displayMode.h;
    scaleX = displayMode.w / 1000.1f;
    scaleY = displayMode.h / 1000.1f;
    SDL_SetWindowResizable(gameWindow, SDL_TRUE);
    renderer = SDL_CreateRenderer(gameWindow, -1, 0);
    if (!renderer)
    {
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

void Game::handleEvents()
{
    while (true)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);
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

                scaleX = (float)width / originalWidth;
                scaleY = (float)height / originalHeight;



                drawer->drawAll();
            }
        }
        else if (event.type == SDL_KEYDOWN)
        {
            uint32_t key = event.key.keysym.sym;
            if (eventHandlers.find(KEYDOWN) != eventHandlers.end())
            {
                Event e;
                e.type = EventType::KEYDOWN;
                e.key = key;
                eventHandlers[KEYDOWN](e);
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            uint32_t key = event.key.keysym.sym;
            if (eventHandlers.find(KEYUP) != eventHandlers.end())
            {
                Event e;
                e.type = EventType::KEYUP;
                e.key = key;
                eventHandlers[KEYUP](e);
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (eventHandlers.find(MOUSEBUTTONDOWN) != eventHandlers.end())
            {
                Event e;
                e.type = EventType::MOUSEBUTTONDOWN;
                e.mouseButton = event.button.button;
                eventHandlers[MOUSEBUTTONDOWN](e);
            }
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (eventHandlers.find(MOUSEBUTTONUP) != eventHandlers.end())
            {
                Event e;
                e.type = EventType::MOUSEBUTTONUP;
                e.mouseButton = event.button.button;
                eventHandlers[MOUSEBUTTONUP](e);
            }
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
            if (eventHandlers.find(MOUSEMOTION) != eventHandlers.end())
            {
                Event e;
                e.type = EventType::MOUSEMOTION;
                e.mousePosition.x = event.motion.x;
                e.mousePosition.y = event.motion.y;
                eventHandlers[MOUSEMOTION](e);
            }
        }
        else if (event.type == SDL_MOUSEWHEEL)
        {
            if (eventHandlers.find(MOUSEWHEEL) != eventHandlers.end())
            {
                Event e;
                e.type = EventType::MOUSEWHEEL;
                e.mouseWheel.x = event.wheel.x;
                e.mouseWheel.y = event.wheel.y;
                eventHandlers[MOUSEWHEEL](e);
            }
        }
    }
}

void Game::addObject(Object object)
{
    objects.push_back(std::make_unique<Object>(std::move(object)));
}

Object *Game::getObject(int index)
{
    return objects.at(index).get();
}

void Game::setEventHandler(EventType eventType, std::function<void (Event &)> handler)
{
    eventHandlers[eventType] = handler;
}

int Game::getWindowWidth()
{
    return width;
}

int Game::getWindowHeight()
{
    return height;
}
