#pragma once

#include "../Types/Component.h"
#include "../Types/Object.h"

class FilledEllipse : public Component
{
public:
    FilledEllipse(Object *object);
    ~FilledEllipse();
    void draw(Object *object) override;
    void onEvent(Event& event) override {}

    std::unique_ptr<Component> clone() const override;
};