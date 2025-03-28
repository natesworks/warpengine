#pragma once

#include <functional>

#include "../Types/Component.h"
#include "../Types/Object.h"

class BoxCollider : public Component
{
public:
    BoxCollider(Object *object, bool isTrigger = false);
    ~BoxCollider();
    void draw(Object *object) override;
    void onEvent(Event &event) override;

    std::unique_ptr<Component> clone() const override;

private:
    Object *object;
    bool isTrigger;
};