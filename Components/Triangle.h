#pragma once

#include "../Types/Component.h"
#include "../Types/Object.h"

class Triangle : public Component
{
public:
    Triangle(Object *object);
    ~Triangle();
    void draw(Object *object) override;
};