#pragma once

#include "../../Types/Component.h"
#include "../../Types/Object.h"
#include "../../Types/Event.h"
#include "../../Types/Vector2.h"

class Rigidbody : public Component
{
public:
    Rigidbody(Object *object, float mass = 1.0f, float gravity = 9.81f,
              Vector2 force = Vector2(0, 0), Vector2 friction = Vector2(0, 0));
    ~Rigidbody();
    void update() override;

    /* Setters and Getters */
    /* Defined in here, because I am lazy */
    void setMass(float mass);
    float getMass() const;
    void setGravity(float gravity);
    float getGravity() const;
    
    void applyForce(Vector2 force);

private:
    Object *object;
    float mass;
    float gravity;
    Vector2 force;
    Vector2 friction;
    Vector2 velocity;
    Vector2 acceleration;
};