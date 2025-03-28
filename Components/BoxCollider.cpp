#include <iostream>
#include <functional>

#include "BoxCollider.h"

BoxCollider::BoxCollider(Object *object, bool isTrigger)
{
    this->object = object;
    this->isTrigger = isTrigger;
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::draw(Object *object)
{
}

void BoxCollider::onEvent(Event &event)
{
    if (event.type == OBJECTPOSITIONCHANGED && event.object == object)
    {
        if (isTrigger)
        {
            // TODO
        }
        else
        {
            for (const auto& objPtr : object->game->objects)
            {
                Object& obj = *objPtr;
                if (&obj != object)
                {
                    if (obj.isColliding(object))
                    {
                        object->setPosition(object->previousPosition);
                    }
                }
            }
        }
    }
}

std::unique_ptr<Component> BoxCollider::clone() const
{
    return std::make_unique<BoxCollider>(*this);
}