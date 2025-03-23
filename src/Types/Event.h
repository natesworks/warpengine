#pragma once

#include <cstdint>

#include "../Enums/EventType.h"
#include "Vector2.h"

struct Event
{
public:
    EventType type;
    uint32_t key; // only for KEYDOWN and KEYUP
    uint8_t mouseButton;
    Vector2 mousePosition; // only for MOUSEMOTION
    Vector2 mouseWheel; // only for MOUSEWHEEL
};