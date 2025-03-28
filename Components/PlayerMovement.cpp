#include <iostream>

#include "PlayerMovement.h"
#include "../Types/Keys.h"

PlayerMovement::PlayerMovement(Object *object, float speed)
{
    this->object = object;
    this->speed = speed;
}

PlayerMovement::~PlayerMovement()
{

}

void PlayerMovement::draw(Object *object)
{

}

void PlayerMovement::onEvent(Event &event)
{
    if (event.type == EventType::KEYDOWN)
    {
        if (event.key == KEY_W)
        {
            object->setPosition(Vector2(object->getPosition().x, object->getPosition().y - speed));
        }
        else if (event.key == KEY_A)
        {
            object->setPosition(Vector2(object->getPosition().x - speed, object->getPosition().y));
        }
        else if (event.key == KEY_S)
        {
            object->setPosition(Vector2(object->getPosition().x, object->getPosition().y + speed));
        }
        else if (event.key == KEY_D)
        {
            object->setPosition(Vector2(object->getPosition().x + speed, object->getPosition().y));
        }
    }
}

std::unique_ptr<Component> PlayerMovement::clone() const
{
    return std::make_unique<PlayerMovement>(*this);
}