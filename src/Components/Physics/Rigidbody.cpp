#include "Rigidbody.h"

Rigidbody::Rigidbody(Object *object, float mass, float gravity, Vector2 friction)
	: object(object)
	, mass(mass)
	, gravity(gravity)
	, force(0, 0)
	, friction(friction)
	, velocity(0, 0)

{
}

Rigidbody::~Rigidbody() { }

void Rigidbody::fixedUpdate()
{
	Vector2 totalForce = force + Vector2(0, mass * gravity);
	Vector2 acceleration = totalForce / mass;
	velocity += acceleration;

	velocity.x *= (1.0f - friction.x);
	velocity.y *= (1.0f - friction.y);

	object->setPosition(object->getPosition() + velocity);

	force = Vector2(0, 0);
}

void Rigidbody::applyForce(Vector2 force)
{
	this->force += force;
}

void Rigidbody::setMass(float mass)
{
	this->mass = mass;
}

float Rigidbody::getMass() const
{
	return mass;
}

void Rigidbody::setGravity(float gravity)
{
	this->gravity = gravity;
}

float Rigidbody::getGravity() const
{
	return gravity;
}
