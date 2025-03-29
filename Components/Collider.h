#pragma once

#include <functional>

#include "../Types/Component.h"
#include "../Types/Object.h"

class Collider : public Component
{
public:
    Collider(Object *object, std::function<void()> onTriggerEnter = nullptr);
    Collider(Object *object);
    virtual ~Collider() = default;

    void setOnTriggerEnter(std::function<void()> onTriggerEnter = nullptr);

    Object *object;
    std::function<void()> onTriggerEnter;

    void callOnTriggerEnter(Object &object);
};
