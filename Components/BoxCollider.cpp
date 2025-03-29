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

std::unique_ptr<Component> BoxCollider::clone() const
{
    return std::make_unique<BoxCollider>(*this);
}

BoxCollider::~BoxCollider() {}
void BoxCollider::draw(Object *object) {}