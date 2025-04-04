#pragma once

#include <functional>

#include "../Types/Component.h"
#include "../Types/Object.h"
#include "Collider.h"

class BoxCollider : public Collider
{
public:
    BoxCollider(Object *object, std::function<void()> onTriggerEnter = nullptr);
    ~BoxCollider();
    void draw(Object *object) override;
    void onEvent(Event &event) override;
    bool isColliding(Rect rect) override;
    bool isColliding(Object *object) override;
};