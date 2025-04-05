#include <iostream>
#include <functional>

#include "BoxCollider.h"
#include "../Types/Scene.h"

BoxCollider::BoxCollider(Object *object, std::function<void()> onTriggerEnter)
    : Collider(object, onTriggerEnter)
{
}

void BoxCollider::onEvent(Event &event)
{
    if ((event.type == OBJECTPOSITIONCHANGED || event.type == OBJECTROTATIONCHANGED || event.type == OBJECTROTATIONCHANGED) && event.object == object)
    {
        for (const auto &otherPtr : object->game->getActiveScene()->getObjects())
        {
            Object &other = *otherPtr;
            if (other != *object)
            {
                if (callIsColliding(&other))
                {
                    callOnTriggerEnter(object);
                }
            }
        }
    }
}

bool BoxCollider::isColliding(Rect rect)
{
    Rect rect2 = Rect(object->getPosition().x,
                      object->getPosition().y,
                      object->getScale().x, object->getScale().y);

    bool isColliding = rect.x < rect2.x + rect2.w &&
                       rect.x + rect.w > rect2.x &&
                       rect.y < rect2.y + rect2.h &&
                       rect.y + rect.h > rect2.y;

    return isColliding; 
}

bool BoxCollider::isColliding(Object *object)
{
    Rect rect = Rect(object->getPosition().x,
                     object->getPosition().y,
                     object->getScale().x, object->getScale().y);
    return isColliding(rect);
}

BoxCollider::~BoxCollider() {}
