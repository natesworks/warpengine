#include <string>

#include "WindowType.h"

class WindowSettings
{
public:
    WindowSettings(int x, int y, int w, int h, std::string title = "Game", WindowType windowType = WINDOWED)
        : x(x), y(y), w(w), h(h), title(title), windowType(windowType) {}
    
    int x;
    int y;
    int w;
    int h;
    int referenceWidth = 1920;
    int referenceHeight = 1080;
    std::string title;
    WindowType windowType;
};