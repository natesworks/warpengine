#pragma once

#include "../Types/Component.h"
#include "../Types/Object.h"

class Button : public Component
{
public:
    Button(Object *object);
    ~Button();
    void draw(Object *object) override;
    void onEvent(Event &event) override;

    std::unique_ptr<Component> clone() const override;
};