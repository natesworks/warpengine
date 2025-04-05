#pragma once

#include "../../Types/Component.h"
#include "../../Types/Object.h"

class Ellipse : public Component
{
public:
    Ellipse(Object *object);
    ~Ellipse();
    void draw(Object *object) override;
    void onEvent(Event& event) override {}
};