#pragma once

#include "../../Types/Component.h"
#include "../../Types/Object.h"

class FilledEllipse : public Component
{
public:
    FilledEllipse(Object *object);
    ~FilledEllipse();
    void draw(Object *object) override;
};