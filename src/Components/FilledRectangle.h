#pragma once

#include "../Types/Component.h"
#include "../Types/Object.h"

class FilledRectangle : public Component
{
public:
    FilledRectangle(Object *object);
    ~FilledRectangle();
    void draw(Object *object) override;
    void onEvent(Event& event) override {}

    std::unique_ptr<Component> clone() const override;
};