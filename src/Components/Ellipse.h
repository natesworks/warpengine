#pragma once

#include "../Types/Component.h"
#include "../Types/Object.h"

class Ellipse : public Component
{
public:
    Ellipse(Object *object);
    ~Ellipse();
    void draw(Object *object) override;

    std::unique_ptr<Component> clone() const override;
};