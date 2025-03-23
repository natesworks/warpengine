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

class Object
{
public:
    std::vector<std::unique_ptr<Component>> components;
    Vector2 position;
    Vector2 scale;
    float rotation;
    RGB color;
    Game *game;

    void addComponent(const Component& component);

    Component& getComponent(int index);

    bool isMouseOver(Vector2 mousePosition);

    Object(Game* game, Vector2 position, Vector2 scale, float rotation, RGB color) 
        : game(game), position(position), scale(scale), rotation(rotation), color(color) {}
};
