#include "Rectangle.h"
#include "../../Rendering/Drawer.h"
#include "../../Types/Vector2.h"

Rectangle::Rectangle(Object *object)
{
}

Rectangle::~Rectangle()
{
}

void Rectangle::draw(Object *object)
{
    object->game->drawer->drawRectangle(object->getPosition(), Vector2(object->getPosition().x + object->getScale().x, object->getPosition().y + object->getScale().y), object->color, object->getRotation());
}