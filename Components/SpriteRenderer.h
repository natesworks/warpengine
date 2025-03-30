#pragma once

#include <string>

#include "../Types/Component.h"
#include "../Types/Object.h"
#include "../Types/Event.h"

class SpriteRenderer : public Component
{
public:
    SpriteRenderer(Object *object, std::string image);
    ~SpriteRenderer();
    void draw(Object *object) override;
    void onEvent(Event &event) override {}
private:
    std::string image;
};