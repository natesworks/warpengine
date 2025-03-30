#include "Object.h"
#include "../Core/Game.h"
#include "Event.h"
#include "EventType.h"

Object::Object(Game *game, Vector2 position, Vector2 scale, float rotation, RGB color)
    : game(game), position(position), scale(scale), rotation(rotation), color(color), previousPosition(position), id(game->objects.size()), active(true)
{
}

Object::~Object()
{
    for (Component *component : components)
    {
        delete component;
    }
}

bool Object::isColliding(Vector2 position)
{
    if (!active)
        return false;

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
    if (!active || !object->getActive())
        return false;
    
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

void Object::setParent(Object *object)
{
    this->parent = object;
    object->children.push_back(this);
}

void Object::setActive(bool active)
{
    this->active = active;
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

int Object::getID()
{
    return id;
}

Object *Object::getParent()
{
    return parent;
}

bool Object::getActive()
{
    return active;
}

void Object::disown(Object *child)
{
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
    child->parent = nullptr;
}

bool Object::operator!=(const Object &other) const
{
    return this != &other;
}