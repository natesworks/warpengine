#pragma once

#include <string>

#include "../../Types/Component.h"
#include "../../Types/Object.h"

class Image : public Component
{
public:
    Image(Object *object, std::string image);
    ~Image();
    void draw(Object *object) override;

private:
    std::string image;
};