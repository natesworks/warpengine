#include "Rigidbody.h"

Rigidbody::Rigidbody(Object *object, float mass, float gravity, Vector2 force, Vector2 friction)
    : object(object), mass(mass), gravity(gravity), force(force), friction(friction)
{
}

Rigidbody::~Rigidbody() {}

void Rigidbody::update()
{
    Vector2 acceleration = force / mass;

    velocity += acceleration;
    velocity.y += gravity;

    velocity.x *= (1.0f - friction.x);
    velocity.y *= (1.0f - friction.y);

    object->setPosition(object->getPosition() + velocity * object->game->getDeltaTime());

    force = Vector2(0, 0);
}

void Rigidbody::applyForce(Vector2 force)
{
    this->force = force;
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