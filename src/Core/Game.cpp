#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <string>
#include <thread>

#include "../Rendering/Drawer.h"
#include "../Types/Component.h"
#include "../Types/Event.h"
#include "../Types/Scene.h"
#include "Game.h"

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
	uint64_t last = now;
	const double timestep = 1.0f / physicsFPS;
	while (true)
	{
		drawer->drawAll();
		last = now;
		now = SDL_GetPerformanceCounter();
		double frameTimeTicks = now - last;
		deltaTime = frameTimeTicks / (double)SDL_GetPerformanceFrequency();
		fps = (deltaTime > 0) ? 1.0 / deltaTime : 0.0f;
		accumulator += deltaTime;

		SDL_Event event;
		SDL_PollEvent(&event);
		events.clear();

		if (event.type == SDL_QUIT)
		{
			exit(0);
		}
		else if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				Event e;
				e.type = WINDOWRESIZED;
				e.previousWindowSize = Vector2(windowSettings.w, windowSettings.h);
				SDL_GetWindowSize(gameWindow, &windowSettings.w, &windowSettings.h);
				e.newWindowSize = Vector2(windowSettings.w, windowSettings.h);
				handleEvent(e);

				SDL_Rect newViewport = { 0, 0, windowSettings.w, windowSettings.h };
				SDL_RenderSetViewport(renderer, &newViewport);

				scale.x = (float)windowSettings.w / (float)windowSettings.referenceWidth;
				scale.y = (float)windowSettings.h / (float)windowSettings.referenceHeight;
			}
		}
		else if (event.type == SDL_KEYDOWN)
		{
			Event e;
			e.type = KEYDOWNONCE;
			e.key = (uint8_t *)SDL_GetKeyboardState(NULL);
			handleEvent(e);
			if (!event.key.repeat)
			{
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
			Event e;
			e.type = EventType::KEYDOWN;

			uint8_t *keyState = (uint8_t *)SDL_GetKeyboardState(NULL);

			uint8_t i = 0;
			bool anyKeyPressed = false;
			while (true)
			{
				if (i == 255)
				{
					break;
				}
				if (keyState[i] == true)
				{
					anyKeyPressed = true;
					break;
				}
				i++;
			}

			if (anyKeyPressed)
			{
				e.key = keyState;
				handleEvent(e);
			}
		}

		for (std::shared_ptr<Object> object : activeScene->getObjects())
		{
			for (Component *component : object->components)
			{
				component->update();
			}
		}

		while (accumulator >= timestep)
		{
			for (std::shared_ptr<Object> object : activeScene->getObjects())
			{
				for (Component *component : object->components)
				{
					component->fixedUpdate();
				}
			}
			accumulator -= timestep;
		}
	}
}

void Game::start(bool sameThread)
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
	if (sameThread)
	{
		gameLoop();
		return;
	}
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

void Game::handleEvent()
{
	for (Event event : events)
	{
		handleEvent(event);
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

std::shared_ptr<Scene> Game::createScene(const std::string &name)
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(this, name);
	scenes.push_back(scene);
	return scene;
}

void Game::loadScene(const std::string &name)
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

std::shared_ptr<Scene> Game::getScene(const std::string &name)
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

std::vector<Event> Game::getEvents()
{
	return events;
}

void Game::handleEvent(Event event)
{
	std::lock_guard<std::mutex> lock(eventsMutex);
	events.push_back(event);
	if (eventHandlers.find(event.type) != eventHandlers.end())
	{
		for (std::function<void(Event & event)> handler : eventHandlers[event.type])
		{
			handler(event);
		}
	}
	for (std::shared_ptr<Object> object : activeScene->getObjects())
	{
		for (Component *component : object->components)
		{
			component->onEvent(event);
		}
	}
}
