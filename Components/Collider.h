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
    void callOnTriggerEnter(Object *collider);
    bool callIsColliding(Object *collider);
    virtual bool isColliding(Object *object);
    virtual bool isColliding(Rect rect);

    Object *object;
    std::function<void()> onTriggerEnter;

};
