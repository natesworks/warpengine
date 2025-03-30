#pragma once

#include "../Types/Component.h"
#include "../Types/Object.h"
#include "../Types/Event.h"

class FilledTriangle : public Component
{
public:
    FilledTriangle(Object *object);
    ~FilledTriangle();
    void draw(Object *object) override;
    void onEvent(Event &event) override {}
};