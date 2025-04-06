#pragma once

#include "Event.h"

class Event;
class Object;

class Component
{
public:
	virtual ~Component() = default;
	virtual void draw(Object* object) { };
	virtual void onEvent(Event& event) { };
	virtual void update() { };
	virtual void fixedUpdate() { };
};
