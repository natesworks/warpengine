#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <cmath>

#include "../Types/Component.h"
#include "Vector2.h"
#include "../Game.h"
#include "../Types/RGB.h"

class Game;
class Component;

class Object
{
public:
    std::vector<std::unique_ptr<Component>> components;
    RGB color;
    Game *game;

    void addComponent(const Component& component);
    Component& getComponent(int index);

    bool isColliding(Vector2 position);
    bool isColliding(Object* object);

    void setPosition(Vector2 position);
    void setScale(Vector2 scale);
    void setRotation(float rotation);

    Vector2 getPosition();
    Vector2 getScale();
    
    float getRotation();

    Vector2 previousPosition;

    Object(Game* game, Vector2 position, Vector2 scale, float rotation, RGB color) 
        : game(game), position(position), scale(scale), rotation(rotation), color(color), previousPosition(position) {}
private:
    Vector2 position;
    Vector2 scale;
    float rotation;
};
