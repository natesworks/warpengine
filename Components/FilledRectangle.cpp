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
    object->game->drawer->drawFilledRectangle(object->getPosition(), Vector2(object->getPosition().x + object->getScale().x, object->getPosition().y + object->getScale().y), object->color, object->getRotation());
}