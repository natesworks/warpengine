#pragma once

#include "../../Types/Component.h"
#include "../../Types/Object.h"

class PlayerMovement : public Component
{
public:
    PlayerMovement(Object *object, float speed = 10);
    ~PlayerMovement();
    void onEvent(Event &event) override;
private:
    Object *object;
    float speed;
};