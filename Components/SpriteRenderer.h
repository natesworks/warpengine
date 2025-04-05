#pragma once

#include <string>

#include "../Types/Component.h"
#include "../Types/Object.h"

class SpriteRenderer : public Component
{
public:
    SpriteRenderer(Object *object, std::string image);
    ~SpriteRenderer();
    void draw(Object *object) override;
private:
    std::string image;
};