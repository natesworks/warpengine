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
    object->game->drawer->drawFilledEllipse(Vector2(object->getPosition().x + object->getScale().x / 2, object->getPosition().y + object->getScale().y / 2), object->getScale().x / 2, object->getScale().y / 2, object->color, object->getRotation());
}

std::unique_ptr<Component> FilledEllipse::clone() const
{
    return std::make_unique<FilledEllipse>(*this);
}