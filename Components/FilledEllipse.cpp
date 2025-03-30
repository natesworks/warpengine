#include "FilledEllipse.h"
#include "../Rendering/Drawer.h"

FilledEllipse::FilledEllipse(Object *object)
{
    draw(object);
}

FilledEllipse::~FilledEllipse()
{

}

void FilledEllipse::draw(Object *object)
{
    object->game->drawer->drawFilledEllipse(Vector2(object->getPosition().x + object->getScale().x, object->getPosition().y + object->getScale().y), Vector2(object->getScale().x, object->getScale().y), object->color, object->getRotation());
}