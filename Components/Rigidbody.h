#pragma once

#include "../Types/Component.h"
#include "../Types/Object.h"
#include "../Types/Event.h"

class Rigidbody : public Component
{
public:
    Rigidbody(Object *object);
    ~Rigidbody();
    void onEvent(Event &event) override;
};