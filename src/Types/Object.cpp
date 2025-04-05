#include "Object.h"
#include "../Core/Game.h"
#include "Event.h"
#include "EventType.h"
#include "../Components/Collider/Collider.h"
#include "Component.h"
#include "../Types/Scene.h"

Object::Object(Game *game, Vector2 position, Vector2 scale, float rotation, RGB color)
    : game(game), position(position), scale(scale), rotation(rotation), color(color), id(game->getActiveScene()->getObjects().size()), active(true)
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

/**
 * @brief Sets object position
 * @param position Object position
 */
void Object::setPosition(Vector2 position)
{
    Event e(OBJECTPOSITIONCHANGED);
    e.object = this;
    e.previousPosition = this->position;
    this->position = position;

    game->handleEvent(e);
}

/**
 * @brief Sets object scale
 * @param scale Object scale
 */
void Object::setScale(Vector2 scale)
{
    Event e(OBJECTSCALECHANGED);
    e.object = this;
    e.previousScale = this->scale;
    this->scale = scale;

    game->handleEvent(e);
}

/**
 * @brief Sets object rotation
 * @param rotation Object rotation
 */
void Object::setRotation(float rotation)
{
    Event e(OBJECTROTATIONCHANGED);
    e.object = this;
    e.previousRotation = this->rotation;
    this->rotation = rotation;

    game->handleEvent(e);
}

/**
 * @brief Sets parent to pointer to object and adds this object as child to parent
 * @param object Pointer to parent object
 */
void Object::setParent(Object *object)
{
    this->parent = object;
    object->children.push_back(this);
}

/**
 * @brief Sets object active or inactive
 * @param active True to set active, false to set inactive
 */
void Object::setActive(bool active)
{
    this->active = active;
}

/**
 * @brief Returns object color
 * @returns Object color
 */
Vector2 Object::getPosition()
{
    return position;
}

/**
 * @brief Returns object scale
 * @returns Object scale
 */
Vector2 Object::getScale()
{
    return scale;
}

/**
 * @brief Returns object rotation
 * @returns Object rotation
 */
float Object::getRotation()
{
    return rotation;
}

/**
 * @brief Returns object id
 * @returns Object id
 */
int Object::getID()
{
    return id;
}

/**
 * @brief Returns pointer to the parent object or nullptr
 * @returns Pointer to parent object
 */
Object *Object::getParent()
{
    return parent;
}

/**
 * @details Inactive objects aren't drawn and collision isn't taken into account
 * @returns Is object active
 */
bool Object::getActive()
{
    return active;
}

/**
 * @brief Removes pointer to child from parent and sets parent to nullptr for child
 * @param child Pointer to child object
 */
void Object::disown(Object *child)
{
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
    child->parent = nullptr;
}

/**
 * @brief Checks if rect collides with any other object
 * TODO Take rotation into account
 */
bool Object::isColliding(Rect rect)
{
    for (Object *object : game->getActiveScene()->getObjects())
    {
        if (*object != *this && object->active)
        {
            for (Component *component : object->components)
            {
                Collider *collider = dynamic_cast<Collider *>(component);
                if (collider != nullptr && collider->isColliding(rect))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * @brief Checks if object collides with any other object
 * TODO Take rotation into account
 */
bool Object::isColliding()
{
    return isColliding(Rect(position.x, position.y, scale.x, scale.y));
}

/**
 * @brief Finds the closest ("safe") position not inside collider and moves the object there
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
        Rect testRectX = Rect(position.x + step, position.y, scale.x, scale.y);
        if (!isColliding(testRectX))
        {
            position.x += step;
            return;
        }

        testRectX = Rect(position.x - step, position.y, scale.x, scale.y);
        if (!isColliding(testRectX))
        {
            position.x -= step;
            return;
        }

        Rect testRectY = Rect(position.x, position.y + step, scale.x, scale.y);
        if (!isColliding(testRectY))
        {
            position.y += step;
            return;
        }

        testRectY = Rect(position.x, position.y - step, scale.x, scale.y);
        if (!isColliding(testRectY))
        {
            position.y -= step;
            return;
        }

        step += 0.1f;
    }
}

/**
 * @brief Returns the center of the object
 */
Vector2 Object::getCenter()
{
    return Vector2(position.x + scale.x / 2, position.y + scale.y / 2);
}

bool Object::operator==(const Object &other) const
{
    return this == &other;
}

bool Object::operator!=(const Object &other) const
{
    return this != &other;
}