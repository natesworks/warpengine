#pragma once

#include <vector>
#include <memory>

class Component
{
public:
    virtual ~Component() = default;

    virtual std::unique_ptr<Component> clone() const = 0;
};
