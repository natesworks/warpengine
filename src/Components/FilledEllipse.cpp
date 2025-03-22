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
    object->game->drawer->drawFilledEllipse(Point(object->position.x, object->position.y), object->scale.x, object->scale.y, object->color);
}

std::unique_ptr<Component> FilledEllipse::clone() const
{
    return std::make_unique<FilledEllipse>(*this);
}