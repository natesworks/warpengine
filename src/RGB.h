#include <cstdint>

class RGB
{
public:
    RGB(uint8_t r, uint8_t g, uint8_t b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    uint8_t r;
    uint8_t g;
    uint8_t b;
};