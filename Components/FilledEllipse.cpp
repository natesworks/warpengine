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
    object->game->drawer->drawFilledEllipse(object->getCenter(), object->getScale() / 2, object->color, object->getRotation());
}