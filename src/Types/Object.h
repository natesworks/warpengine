#pragma once

#include <vector>
#include <memory>

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

    void addComponent(const Component& component)
    {
        components.push_back(component.clone());
    }

    Component& getComponent(int index)
    {
        return *components.at(index);
    }

    bool isMouseOver(Vector2 mousePosition)
    {
        return mousePosition.x >= position.x && mousePosition.x <= position.x + scale.x && mousePosition.y >= position.y && mousePosition.y <= position.y + scale.y;
    }

    Object(Game* game, Vector2 position, Vector2 scale, float rotation, RGB color) 
        : game(game), position(position), scale(scale), rotation(rotation), color(color) {}
};
