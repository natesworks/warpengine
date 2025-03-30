#pragma once

#include "../Types/Component.h"
#include "../Types/Object.h"
#include "../Types/Event.h"

class Triangle : public Component
{
public:
    Triangle(Object *object);
    ~Triangle();
    void draw(Object *object) override;
    void onEvent(Event &event) override {}
};