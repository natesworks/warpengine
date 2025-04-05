#pragma once

#include <functional>

#include "../Types/Object.h"
#include "Collider.h"

class BoxCollider : public Collider
{
public:
    BoxCollider(Object *object, std::function<void()> onTriggerEnter = nullptr);
    ~BoxCollider();
    void onEvent(Event &event) override;
    bool isColliding(Rect rect) override;
    bool isColliding(Object *object) override;
};