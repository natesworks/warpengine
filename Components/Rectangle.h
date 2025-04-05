#pragma once

#include "../Types/Component.h"
#include "../Types/Object.h"

class Rectangle : public Component
{
public:
    Rectangle(Object *object);
    ~Rectangle();
    void draw(Object *object) override;
};