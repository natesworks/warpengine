#include "Ellipse.h"
#include "../Rendering/Drawer.h"
#include "../Types/Vector2.h"

Ellipse::Ellipse(Object *object)
{
}

Ellipse::~Ellipse()
{
}

void Ellipse::draw(Object *object)
{
    object->game->drawer->drawEllipse(object->getPosition(), Vector2(object->getScale().x, object->getScale().y), object->color, object->getRotation());
}