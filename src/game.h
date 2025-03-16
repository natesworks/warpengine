#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <string>

class Game
{
public:
    Game(int x, int y, int w, int h, std::string title = "Game", bool borderless = false);
    Game(int w, int h, std::string title = "Game", bool borderless = false);
    Game(std::string title = "Game");
private:
    SDL_Window *gameWindow = nullptr;
    SDL_Renderer *renderer = nullptr;
};

class InitialisationFailed
{

};