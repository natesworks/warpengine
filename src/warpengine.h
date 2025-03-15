#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <string>

class Game
{
public:
    Game(int x, int y, int w, int h, std::string title = "Warp Engine");
    Game(std::string title = "Warp Engine");
private:
    SDL_Window *gameWindow = nullptr;
};

class InitialisationFailed
{

};