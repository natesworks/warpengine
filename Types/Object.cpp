#include "Object.h"
#include "../Core/Game.h"
#include "Event.h"
#include "EventType.h"
#include "../Components/Collider.h"
#include "Component.h"

Object::Object(Game *game, Vector2 position, Vector2 scale, float rotation, RGB color)
    : game(game), position(position), scale(scale), rotation(rotation), color(color), id(game->objects.size()), active(true)
{
}

Object::~Object()
{
    for (Component *component : components)
    {
        delete component;
    }
}

/**
 * @brief Checks if position overlaps with object
 * TODO Take rotation into account
 */
bool Object::isOverlapping(Vector2 position)
{
    if (!active)
        return false;

    position = position * game->scale;
    Vector2 position2 = this->position * game->scale;

    if (position.x > position2.x && position.x < position2.x + scale.x && position.y > position2.y && position.y < position2.y + scale.y)
    {
        return true;
    }

    return false;
}

void Object::setPosition(Vector2 position)
{
    Event e(OBJECTPOSITIONCHANGED);
    e.object = this;
    e.previousPosition = this->position;
    this->position = position;

    game->handleEvent(e);
}

void Object::setScale(Vector2 scale)
{
    Event e(OBJECTSCALECHANGED);
    e.object = this;
    e.previousScale = this->scale;
    this->scale = scale;

    game->handleEvent(e);
}

void Object::setRotation(float rotation)
{
    Event e(OBJECTROTATIONCHANGED);
    e.object = this;
    e.previousRotation = this->rotation;
    this->rotation = rotation;

    game->handleEvent(e);
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

bool Object::isColliding()
{
    for (Object *object : game->objects)
    {
        if (*object != *this && object->active)
        {
            for (Component *component : components)
            {
                Collider *collider = dynamic_cast<Collider *>(component);
                if (collider != nullptr && collider->isColliding(object))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * @brief Finds the closest ("safe") position not inside collider and moves the object to there
 */
void Object::findSafePosition()
{
    Collider *collider = nullptr;

    for (Component *component : components)
    {
        Collider *foundCollider = dynamic_cast<Collider *>(component);
        if (foundCollider != nullptr)
        {
            collider = foundCollider;
            break;
        }
    }

    if (collider == nullptr || !isColliding())
    {
        return;
    }

    float step = 0.1f;

    while (true)
    {
        for (float angle = 0.0f; angle < 360.0f; angle += 10.0f)
        {
            float radian = angle * (M_PI / 180.0f);
            Vector2 offset(step * cos(radian), step * sin(radian));
            
            Rect testRect = Rect(position.x + offset.x,
                                 position.y + offset.y,
                                 scale.x, scale.y);

            if (!collider->isColliding(testRect))
            {
                position += offset;        
                findSafePosition();  
                return;
            }
        }
        step += 0.1f;
    }
}