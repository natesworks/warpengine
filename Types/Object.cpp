#include "Object.h"
#include "../Game.h"
#include "Event.h"
#include "EventType.h"

void Object::addComponent(const Component &component)
{
    components.push_back(component.clone());
}

Component &Object::getComponent(int index)
{
    return *components.at(index);
}

bool Object::isColliding(Vector2 position)
{
    int x = this->position.x;
    int y = this->position.y;
    bool isColliding = false;

    if (position.x > x * game->scale.x && position.x < x * game->scale.x + scale.x && position.y > y * game->scale.y && position.y < y * game->scale.y + scale.y)
    {
        isColliding = true;
    }

    return isColliding;
}

bool Object::isColliding(Object *object)
{
    int x = this->position.x * game->scale.x;
    int y = this->position.y * game->scale.y;
    int objX = object->position.x * game->scale.x;
    int objY = object->position.y * game->scale.y;
    bool isColliding = false;

    if (x < objX + object->scale.x / 2 &&
        x + scale.x / 2 > objX &&
        y < objY + object->scale.y / 2 &&
        y + scale.y / 2 > objY)
    {
        isColliding = true;
    }

    return isColliding;
}

void Object::setPosition(Vector2 position)
{
    previousPosition = this->position;
    this->position = position;
    Event e(OBJECTPOSITIONCHANGED);
    e.object = this;

    game->handleEvent(e);
}

void Object::setScale(Vector2 scale)
{
    this->scale = scale;
}

void Object::setRotation(float rotation)
{
    this->rotation = rotation;
}

Vector2 Object::getPosition()
{
    return position;
}

Vector2 Object::getScale()
{
    return scale;
}

float Object::getRotation()
{
    return rotation;
}