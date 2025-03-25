#pragma once

#include <functional>

#include "../Types/Component.h"
#include "../Types/Object.h"

class BoxCollider : public Component
{
public:
    BoxCollider(Object *object, std::function<void()> onTriggerEnter = []() {});
    ~BoxCollider();
    void draw(Object *object) override;
    void onEvent(Event &event) override;
    void setOnTriggerEnterFunction(std::function<void()> onTriggerEnter);

    std::unique_ptr<Component> clone() const override;

private:
    std::function<void()> onTriggerEnter;
};