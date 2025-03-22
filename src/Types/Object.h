#pragma once

#include <vector>
#include <memory>

#include "Vector2.h"
#include "../Game.h"
#include "../Types/Component.h"
#include "../Types/RGB.h"

class Game;

class Object
{
public:
    std::vector<std::unique_ptr<Component>> components;
    Vector2 position;
    Vector2 scale;
    Vector2 rotation;
    RGB color;
    Game *game;

    void addComponent(const Component& component)
    {
        components.push_back(component.clone());
    }

    Component& getComponent(int index)
    {
        return *components.at(index);
    }

    Object(Game* game, Vector2 position, Vector2 scale, Vector2 rotation, RGB color) : game(game), position(position), scale(scale), rotation(rotation), color(color) {};
};
