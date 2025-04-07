#include <stdexcept>

#include "CharacterController.h"
#include "../../Types/Keys.h"
#include "../Physics/Rigidbody.h"

CharacterController::CharacterController(Object *object, float speed)
	: object(object)
	, speed(speed)
{
}

CharacterController::~CharacterController() { }

void CharacterController::fixedUpdate()
{
	bool foundEvent = false;
	Event event;

	for (Event e : object->game->getEvents())
	{
		if (e.type == KEYDOWN)
		{
			event = e;
			foundEvent = true;
			break;
		}
	}

	if (!object->getActive() || !foundEvent)
	{
		return;
	}

	Rigidbody *rigidbody = object->getComponent<Rigidbody>();
	if (!rigidbody)
	{
		throw std::runtime_error("Rigidbody not found");
	}

	if (event.type == KEYDOWN)
	{
		if (event.key[KEY_W] || event.key[KEY_SPACE] || event.key[KEY_UP])
		{
			rigidbody->applyForce(Vector2(0, -speed));
		}
			
		if (event.key[KEY_A] || event.key[KEY_RIGHT])
		{
			rigidbody->applyForce(Vector2(-speed, 0));
		}
		if (event.key[KEY_D] || event.key[KEY_LEFT)
		{
			rigidbody->applyForce(Vector2(speed, 0));
		}
	}
}
