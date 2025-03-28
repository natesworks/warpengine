#pragma once

#include <cstdint>

#include "EventType.h"
#include "Object.h"
#include "Vector2.h"

class Object;

class Event
{
public:
    EventType type;
    uint8_t *key; // only for KEYDOWN and KEYUP
    uint8_t mouseButton;
    Vector2 mousePosition; // only for MOUSEMOTION
    Vector2 mouseWheel; // only for MOUSEWHEEL
    Object* object; // only for OBJECTPOSITIONCHANGED
    Event (EventType type) : type(type) {}
    Event () {}
};
