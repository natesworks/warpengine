#pragma once

#include <memory>

#include "Event.h"

class Object;

class Component
{
public:
    virtual ~Component() = default;
    virtual void draw(Object* object) = 0;
    virtual void onEvent(Event& event) = 0;
    virtual std::unique_ptr<Component> clone() const = 0;
};
