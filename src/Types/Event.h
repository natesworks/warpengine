#pragma once

#include <cstdint>

#include "EventType.h"
#include "Object.h"
#include "Vector2.h"

class Object;

class Event
{
public:
	EventType type;
	uint8_t* key; // for KEYDOWN and KEYUP
	uint8_t mouseButton;
	Vector2 mousePosition; // for MOUSEMOTION
	Vector2 mouseWheel; // for MOUSEWHEEL
	Object* object; // for object attribute changes
	Vector2 previousPosition; // for OBJECTPOSITIONCHANGED
	Vector2 previousScale; // for OBJECTSCALECHANGED
	float previousRotation; // for OBJECTROTATIONCHANGES

	/* Window Resize Event */
	Vector2 previousWindowSize;
	Vector2 newWindowSize;

	Event(EventType type)
		: type(type)
	{
	}
	Event() { }
};
