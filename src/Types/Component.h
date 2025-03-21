#pragma once

#include <vector>
#include <memory>

#include "Object.h"

class Object;

class Component
{
public:
    virtual ~Component() = default;

    virtual std::unique_ptr<Component> clone() const = 0;
};
