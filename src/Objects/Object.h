#pragma once

#include <vector>
#include <memory>

#include "../RGB.h"

class Object {
public:
    virtual ~Object() = default;
    
    virtual std::unique_ptr<Object> clone() const = 0;
    
    RGB color;
    
    Object(RGB color) : color(color) {}
};
