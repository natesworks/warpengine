#pragma once

#include "../Types/Component.h"
#include "../Types/Object.h"
#include "../Types/Event.h"

class Rectangle : public Component
{
public:
    Rectangle(Object *object);
    ~Rectangle();
    void draw(Object *object) override;
    void onEvent(Event& event) override {}

    std::unique_ptr<Component> clone() const override;
};