#include "Object.h"
#include "../Game.h"

void Object::addComponent(const Component& component)
{
    components.push_back(component.clone());
}

Component& Object::getComponent(int index)
{
    return *components.at(index);
}

bool Object::isMouseOver(Vector2 mousePosition)
{
    int x = position.x;
    int y = position.y;
    bool isMouseOver;

    /*
    std::cout << "Mouse Position: " << mousePosition.x << ", " << mousePosition.y << "\n";
    std::cout << "Object Position: " << x << ", " << y << "\n";
    std::cout << "Scale: " << scale.x << ", " << scale.y << "\n";
    std::cout << "Window scale: " << game->scaleX << ", " << game->scaleY << "\n\n";
    */

    if (mousePosition.x > x * game->scaleX && mousePosition.x < x * game->scaleX + scale.x && mousePosition.y > y * game->scaleY && mousePosition.y < y * game->scaleY + scale.y)
    {
        isMouseOver = true;
    }
    else
    {
        isMouseOver = false;
    }

    return isMouseOver;
}

void Object::setPosition(Vector2 position)
{
    this->position = position;
}

void Object::setScale(Vector2 scale)
{
    this->scale = scale;
}

void Object::setRotation(float rotation)
{
    this->rotation = rotation;
}

Vector2 Object::getPosition()
{
    return position;
}

Vector2 Object::getScale()
{
    return scale;
}

float Object::getRotation()
{
    return rotation;
}