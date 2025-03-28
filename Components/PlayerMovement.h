#pragma once

#include "../Types/Component.h"
#include "../Types/Object.h"

class PlayerMovement : public Component
{
public:
    PlayerMovement(Object *object, float speed = 10);
    ~PlayerMovement();
    void draw(Object *object) override;
    void onEvent(Event &event) override;

    std::unique_ptr<Component> clone() const override;
private:
    Object *object;
    float speed;
};