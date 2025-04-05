#include <iostream>

#include "CharacterController.h"
#include "../../Types/Keys.h"

CharacterController::CharacterController(Object *object, float speed)
{
    this->object = object;
    this->speed = speed;
}

CharacterController::~CharacterController()
{

}

void CharacterController::onEvent(Event &event)
{
    if (event.type == EventType::KEYDOWN)
    {
        double deltaTime = object->game->getDeltaTime();
        if (event.key[KEY_W])
        {
            object->setPosition(Vector2(object->getPosition().x, object->getPosition().y - speed * deltaTime));
        }
        if (event.key[KEY_A])
        {
            object->setPosition(Vector2(object->getPosition().x - speed * deltaTime, object->getPosition().y));
        }
        if (event.key[KEY_S])
        {
            object->setPosition(Vector2(object->getPosition().x, object->getPosition().y + speed * deltaTime));
        }
        if (event.key[KEY_D])
        {
            object->setPosition(Vector2(object->getPosition().x + speed * deltaTime, object->getPosition().y));
        }
    }
}