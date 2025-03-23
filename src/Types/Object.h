#pragma once

#include <vector>
#include <memory>
#include <iostream>

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
        Vector2 localMousePosition = mousePosition - position;

        float cosTheta = cos(-rotation);
        float sinTheta = sin(-rotation);
        float localX = localMousePosition.x * cosTheta - localMousePosition.y * sinTheta;
        float localY = localMousePosition.x * sinTheta + localMousePosition.y * cosTheta;

        bool isMouseOver = localX >= 0 && localX <= scale.x && localY >= 0 && localY <= scale.y;

        return isMouseOver;
    }

    Object(Game* game, Vector2 position, Vector2 scale, float rotation, RGB color) 
        : game(game), position(position), scale(scale), rotation(rotation), color(color) {}
};
