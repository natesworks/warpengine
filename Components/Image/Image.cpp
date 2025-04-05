#include <string>

#include "Image.h"
#include "../../Rendering/Drawer.h"
#include "../../Types/Vector2.h"

Image::Image(Object *object, std::string image) : image(image)
{
}

Image::~Image()
{
}

void Image::draw(Object *object)
{
    object->game->drawer->drawSprite(image, object->getPosition(), object->getScale(), object->color);
}