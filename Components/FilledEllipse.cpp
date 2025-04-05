#include "FilledEllipse.h"
#include "../Rendering/Drawer.h"

FilledEllipse::FilledEllipse(Object *object)
{
}

FilledEllipse::~FilledEllipse()
{
}

void FilledEllipse::draw(Object *object)
{
    object->game->drawer->drawFilledEllipse(Vector2(object->getPosition().x + object->getScale().x, object->getPosition().y + object->getScale().y), object->getScale(), object->color, object->getRotation());
}