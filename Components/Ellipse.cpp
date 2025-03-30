#include "Ellipse.h"
#include "../Rendering/Drawer.h"
#include "../Types/Vector2.h"

Ellipse::Ellipse(Object *object)
{
    draw(object);
}

Ellipse::~Ellipse()
{

}

void Ellipse::draw(Object *object)
{
    object->game->drawer->drawEllipse(Vector2(object->getPosition().x, object->getPosition().x), Vector2(object->getScale().x, object->getScale().y), object->color, object->getRotation());
}