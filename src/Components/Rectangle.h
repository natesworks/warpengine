#pragma once

#include "../Types/Component.h"
#include "../Types/Object.h"

class Rectangle : public Component
{
public:
    Rectangle(Object *object);
    ~Rectangle();

    std::unique_ptr<Component> clone() const override;
};