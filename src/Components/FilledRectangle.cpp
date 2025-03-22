#include "FilledRectangle.h"
#include "../Rendering/Drawer.h"

FilledRectangle::FilledRectangle(Object *object)
{
    draw(object);
}

FilledRectangle::~FilledRectangle()
{

}

void FilledRectangle::draw(Object *object)
{
    object->game->drawer->drawFilledRectangle(Point(object->position.x, object->position.y), Point(object->position.x + object->scale.x, object->position.y + object->scale.y), object->color);
}

std::unique_ptr<Component> FilledRectangle::clone() const
{
    return std::make_unique<FilledRectangle>(*this);
}