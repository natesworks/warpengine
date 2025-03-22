#include "Ellipse.h"
#include "../Rendering/Drawer.h"

Ellipse::Ellipse(Object *object)
{
    draw(object);
}

Ellipse::~Ellipse()
{

}

void Ellipse::draw(Object *object)
{
    object->game->drawer->drawEllipse(Point(object->position.x, object->position.y), object->scale.x, object->scale.y, object->color);
}

std::unique_ptr<Component> Ellipse::clone() const
{
    return std::make_unique<Ellipse>(*this);
}