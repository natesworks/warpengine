#include "Rectangle.h"
#include "../Rendering/Drawer.h"

Rectangle::Rectangle(Object *object)
{
    draw(object);
}

Rectangle::~Rectangle()
{

}

void Rectangle::draw(Object *object)
{
    object->game->drawer->drawRectangle(Point(object->position.x, object->position.y), Point(object->position.x + object->scale.x, object->position.y + object->scale.y), RGB(0, 0, 255));
}

std::unique_ptr<Component> Rectangle::clone() const
{
    return std::make_unique<Rectangle>(*this);
}