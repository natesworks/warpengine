#pragma once

#include "../../Types/Component.h"
#include "../../Types/Object.h"

class CharacterController : public Component
{
public:
	CharacterController(Object* object, float speed = 10);
	~CharacterController();
	void fixedUpdate() override;

private:
	Object* object;
	float speed;
};
