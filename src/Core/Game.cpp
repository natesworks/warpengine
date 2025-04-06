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
#include "../Types/Scene.h"
#include "../Rendering/Drawer.h"
#include "../Types/Event.h"

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
                SDL_GetWindowSize(gameWindow, &windowSettings.w, &windowSettings.h);

                SDL_Rect newViewport = {0, 0, windowSettings.w, windowSettings.h};
                SDL_RenderSetViewport(renderer, &newViewport);

                scale.x = (float)windowSettings.w / (float)windowSettings.referenceWidth;
                scale.y = (float)windowSettings.h / (float)windowSettings.referenceHeight;
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
                        if (windowSettings.fullscreenType == WINDOWED)
                        {
                            SDL_SetWindowBordered(gameWindow, SDL_TRUE);
                        }
                        else if (windowSettings.fullscreenType == BORDERLESS)
                        {
                            SDL_SetWindowBordered(gameWindow, SDL_FALSE);
                        }
                        SDL_SetWindowFullscreen(gameWindow, 0);
                        SDL_SetWindowResizable(gameWindow, SDL_TRUE);
                    }
                    else
                    {
                        uint32_t fullscreenType;
                        if (windowSettings.fullscreenType == FULLSCREEN)
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
            // fix for if you press two balancing themselves out keys (W and S, A and D) at the same time and then let one go you won't move
            Event e;
            e.type = EventType::KEYDOWN;
            e.key = (uint8_t *)SDL_GetKeyboardState(NULL);
            if (e.key == NULL)
            {
                continue;
            }
            for (int i = 0; i < 512; i++)
            {
                if (e.key[i] == 1)
                {
                    handleEvent(e);
                }
            }
        }
        for (Object *object : activeScene->getObjects())
        {
            for (Component *component : object->components)
            {
                component->update();
            }
        }
    }
}

void Game::start()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        throw InitialisationFailed();
    }

    uint32_t flags = 0;
    if (windowSettings.windowType == BORDERLESS)
    {
        flags = SDL_WINDOW_BORDERLESS;
    }
    else if (windowSettings.windowType == FULLSCREEN)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    else if (windowSettings.windowType == DESKTOPFULLSCREEN)
    {
        flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    drawer = std::make_shared<Drawer>(this);
    gameWindow = SDL_CreateWindow(windowSettings.title.c_str(), windowSettings.x, windowSettings.y, windowSettings.w, windowSettings.h, flags);
    if (!gameWindow)
    {
        throw WindowCreationFailed();
    }

    scale.x = (float)windowSettings.w / (float)windowSettings.referenceWidth;
    scale.y = (float)windowSettings.h / (float)windowSettings.referenceHeight;
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
    std::thread gameLoopThread(&Game::gameLoop, this);
    gameLoopThread.detach();
}

int Game::getWindowWidth()
{
    return windowSettings.w;
}

int Game::getWindowHeight()
{
    return windowSettings.h;
}

void Game::handleEvent(Event &event)
{
    if (eventHandlers.find(event.type) != eventHandlers.end())
    {
        for (std::function<void(Event &event)> handler : eventHandlers[event.type])
        {
            handler(event);
        }
    }
    for (Object *object : activeScene->getObjects())
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

std::shared_ptr<Scene> Game::createScene(const std::string& name)
{
    std::shared_ptr<Scene> scene = std::make_shared<Scene>(this, name);
    scenes.push_back(scene);
    return scene;
}

void Game::loadScene(const std::string& name)
{
    for (std::shared_ptr<Scene> scene : scenes)
    {
        if (scene->getName() == name)
        {
            activeScene = scene;
            return;
        }
    }
    throw SceneNotFound();
}

void Game::loadScene(std::shared_ptr<Scene> scene)
{
    for (std::shared_ptr<Scene> s : scenes)
    {
        if (s->getName() == scene->getName())
        {
            activeScene = s;
            return;
        }
    }
    throw SceneNotFound();
}

std::shared_ptr<Scene> Game::getScene(const std::string& name)
{
    for (std::shared_ptr<Scene> scene : scenes)
    {
        if (scene->getName() == name)
        {
            return scene;
        }
    }
    throw SceneNotFound();
}

std::shared_ptr<Scene> Game::getActiveScene()
{
    return activeScene;
}