#include "Collider.h"

Collider::Collider(Object *object, std::function<void()> onTriggerEnter)
    : object(object), onTriggerEnter(onTriggerEnter)
{
}

void Collider::setOnTriggerEnter(std::function<void()> onTriggerEnter)
{
    this->onTriggerEnter = onTriggerEnter;
}

void Collider::callOnTriggerEnter(Object &object)
{
    for (Component* component : object.components)
    {
        Collider* collider = dynamic_cast<Collider*>(component);

        if (collider != nullptr)
        {
            if (collider->onTriggerEnter != nullptr)
            {
                collider->onTriggerEnter();
            }
            else
            {
                this->object->setPosition(this->object->previousPosition);
            }
        }
    }
}