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

    std::cout << "Mouse position: " << mousePosition.x << ", " << mousePosition.y << std::endl;
    std::cout << "Object position: " << x << ", " << y << std::endl;
    std::cout << "Object position taking into account scale: " << x + scale.x << ", " << y + scale.y << std::endl;
    std::cout << "Object position taking into account window scale: " << x * game->scaleX << ", " << y * game->scaleY << std::endl;
    std::cout << "Object position taking into account both: " << x * game->scaleX + scale.x << ", " << y * game->scaleY + scale.x << std::endl;

    if (mousePosition.x > x * game->scaleX && mousePosition.x < x * game->scaleX + scale.x / 2 && mousePosition.y > y * game->scaleY && mousePosition.y < y * game->scaleY + scale.y / 2)
    {
        std::cout << "Mouse is over object" << std::endl;
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