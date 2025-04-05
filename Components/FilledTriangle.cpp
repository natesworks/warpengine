#include "FilledTriangle.h"
#include "../Rendering/Drawer.h"
#include "../Types/Vector2.h"

FilledTriangle::FilledTriangle(Object *object)
{
}

FilledTriangle::~FilledTriangle()
{
}

void FilledTriangle::draw(Object *object)
{
    object->game->drawer->drawFilledTriangle(object->getPosition(), Vector2(object->getScale().x, object->getScale().y), object->color, object->getRotation());
}