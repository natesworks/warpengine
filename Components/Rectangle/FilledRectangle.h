#pragma once

#include "../../Types/Component.h"
#include "../../Types/Object.h"

class FilledRectangle : public Component
{
public:
    FilledRectangle(Object *object);
    ~FilledRectangle();
    void draw(Object *object) override;
};