#include "Rectangle.h"
#include "../Rendering/Drawer.h"
#include "../Types/Vector2.h"

Rectangle::Rectangle(Object *object)
{
    draw(object);
}

Rectangle::~Rectangle()
{

}

void Rectangle::draw(Object *object)
{
    object->game->drawer->drawRectangle(Vector2(object->getPosition().x, object->getPosition().y), Vector2(object->getPosition().x + object->getScale().x, object->getPosition().y + object->getScale().y), object->color, object->getRotation());
}

std::unique_ptr<Component> Rectangle::clone() const
{
    return std::make_unique<Rectangle>(*this);
}