#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <cmath>

#include "../Types/Component.h"
#include "Vector2.h"
#include "../Core/Game.h"
#include "../Types/RGB.h"

class Game;
class Component;

class Object
{
public:
    std::vector<Component *> components;
    RGB color;
    Game *game;

    Component *addComponent(Component *component);
    Component *getComponent(int index);

    bool isColliding(Vector2 position);
    bool isColliding(Object *object);

    void setPosition(Vector2 position);
    void setScale(Vector2 scale);
    void setRotation(float rotation);

    Vector2 getPosition();
    Vector2 getScale();
    float getRotation();
    int getID();

    Vector2 previousPosition;

    Object(Game *game, Vector2 position, Vector2 scale, float rotation, RGB color);
    ~Object();

    bool operator!=(const Object &other) const;

private:
    Vector2 position;
    Vector2 scale;
    float rotation;
    int id;
};
