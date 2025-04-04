#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <cmath>

#include "Component.h"
#include "Vector2.h"
#include "../Core/Game.h"
#include "RGB.h"
#include "Rect.h"

class Game;
class Component;

class Object
{
public:
    std::vector<Component *> components;
    RGB color;
    Game *game;

    template <typename T, typename... Args>
    Component *addComponent(Args &&...args)
    {
        auto component = new T(this, std::forward<Args>(args)...);
        components.push_back(component);
        return component;
    }

    bool isOverlapping(Vector2 position);
    bool isColliding();

    void setPosition(Vector2 position);
    void setScale(Vector2 scale);
    void setRotation(float rotation);
    void setParent(Object* object);
    void setActive(bool active);
    void findSafePosition();

    Vector2 getPosition();
    Vector2 getScale();
    float getRotation();
    int getID();
    Object* getParent();
    bool getActive();

    template <typename T>
    T* getComponent()
    {
        for (auto component : components)
        {
            if (auto castComponent = dynamic_cast<T*>(component))
            {
                return castComponent;
            }
        }
        return nullptr;
    }    
    void disown(Object* child);

    Object(Game *game, Vector2 position, Vector2 scale, float rotation, RGB color);
    ~Object();

    bool operator!=(const Object &other) const;

private:
    Vector2 position;
    Vector2 scale;
    float rotation;
    int id;
    Object* parent;
    std::vector<Object*> children;
    bool active;
};
