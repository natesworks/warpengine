#include "Collider.h"

Collider::Collider(Object *object, std::function<void()> onTriggerEnter)
    : object(object), onTriggerEnter(onTriggerEnter)
{
}

void Collider::setOnTriggerEnter(std::function<void()> onTriggerEnter)
{
    this->onTriggerEnter = onTriggerEnter;
}

void Collider::callOnTriggerEnter(Object *collider)
{
    for (Component *component : object->components)
    {
        Collider *colliderComponent = dynamic_cast<Collider *>(component);

        if (colliderComponent != nullptr)
        {
            if (colliderComponent->onTriggerEnter != nullptr)
            {
                colliderComponent->onTriggerEnter();
            }
            else
            {
                collider->findSafePosition();
            }
        }
    }
}

bool Collider::callIsColliding(Object *collider)
{
    for (Component *component : object->components)
    {
        Collider *colliderComponent = dynamic_cast<Collider *>(component);

        if (colliderComponent != nullptr)
        {
            return colliderComponent->isColliding(collider);
        }
    }

    return false;
}

bool Collider::isColliding(Object *object)
{
    return false;
}

bool Collider::isColliding(Rect rect)
{
    return false;
}