#include "Triangle.h"
#include "../../Rendering/Drawer.h"
#include "../../Types/Vector2.h"

Triangle::Triangle(Object *object)
{
}

Triangle::~Triangle()
{
}

void Triangle::draw(Object *object)
{
    object->game->drawer->drawTriangle(object->getPosition(), Vector2(object->getScale().x, object->getScale().y), object->color, object->getRotation());
}