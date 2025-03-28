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
    float x = this->position.x * game->scale.x;
    float y = this->position.y * game->scale.y;
    float x2 = object->position.x * game->scale.x;
    float y2 = object->position.y * game->scale.y;

    float w1 = this->scale.x * game->scale.x;
    float w2 = object->scale.x * game->scale.x;
    float h1 = this->scale.y * game->scale.y;
    float h2 = object->scale.y * game->scale.y;

    return (x < x2 + w2 &&
            x + w1 > x2 &&
            y < y2 + h2 &&
            y + h1 > y2);
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