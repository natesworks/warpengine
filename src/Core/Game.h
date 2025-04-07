#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include "../Types/EventType.h"
#include "../Types/Vector2.h"
#include "../Types/WindowSettings.h"
#include "../Types/WindowType.h"

class Scene;
class Object;
class Drawer;
class Event;

class Game
{
public:
	SDL_Renderer *renderer = nullptr;
	Vector2 scale;
	std::shared_ptr<Drawer> drawer;

	template<typename... Args>
	Game(Args &&...args)
		: windowSettings(std::forward<Args>(args)...)
		, physicsFPS(60.0f)
	{
	}
	~Game();

	int addEventHandler(EventType eventType, std::function<void(Event &event)> handler);
	void removeEventHandler(EventType eventType, int index);
	void start(bool sameThread = false);

	int getWindowWidth();
	int getWindowHeight();
	double getDeltaTime();
	double getFPS();

	void handleEvent();
	std::vector<Event> getEvents();
	void handleEvent(Event e);

	bool togglableFullscreen = true;
	WindowSettings windowSettings;

	template<typename... Args>
	std::shared_ptr<Scene> addScene(Args &&...args)
	{
		scenes.push_back(std::make_shared<Scene>(this, std::forward<Args>(args)...));
		return scenes.back();
	}
	void loadScene(const std::string &name);
	std::shared_ptr<Scene> createScene(const std::string &name);
	std::shared_ptr<Scene> getActiveScene();
	std::shared_ptr<Scene> getScene(const std::string &name);

	double physicsFPS;
	std::mutex eventsMutex;

private:
	SDL_Window *gameWindow = nullptr;
	std::vector<std::shared_ptr<Scene>> scenes;
	std::shared_ptr<Scene> activeScene;

	double deltaTime;
	double fps;
	double accumulator;

	void gameLoop();
	std::unordered_map<EventType, std::vector<std::function<void(Event &event)>>> eventHandlers;
	WindowType startingWindowType;
	std::vector<Event> events;
};

/**
 * TODO Move to a separate file
 */
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

class SceneNotFound
{
};
