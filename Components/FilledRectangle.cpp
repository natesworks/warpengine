#include "FilledRectangle.h"
#include "../Rendering/Drawer.h"
#include "../Types/Vector2.h"

FilledRectangle::FilledRectangle(Object *object)
{
    draw(object);
}

FilledRectangle::~FilledRectangle()
{

}

void FilledRectangle::draw(Object *object)
{
    object->game->drawer->drawFilledRectangle(Vector2(object->getPosition().x, object->getPosition().y), Vector2(object->getPosition().x + object->getScale().x, object->getPosition().y + object->getScale().y), object->color, object->getRotation());
}

std::unique_ptr<Component> FilledRectangle::clone() const
{
    return std::make_unique<FilledRectangle>(*this);
}