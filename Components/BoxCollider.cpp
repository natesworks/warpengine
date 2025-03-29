#include <iostream>
#include <functional>

#include "BoxCollider.h"

BoxCollider::BoxCollider(Object *object, std::function<void()> onTriggerEnter)
    : Collider(object, onTriggerEnter)
{
}

void BoxCollider::onEvent(Event &event)
{
    if (event.type == OBJECTPOSITIONCHANGED && event.object->getID() == object->getID())
    {
        for (const auto &otherPtr : object->game->objects)
        {
            Object &other = *otherPtr;
            if (other != *object)
            {
                if (object->isColliding(&other))
                {
                    callOnTriggerEnter(other);
                }
            }
        }
    }
}

BoxCollider::~BoxCollider() {}
void BoxCollider::draw(Object *object) {}