#include <algorithm>

#include "Scene.h"

Scene::Scene(Game *game, std::string name) : game(game), name(name) {}

void Scene::removeObject(Object *object)
{
    auto it = std::find(objects.begin(), objects.end(), object);
    if (it != objects.end())
    {
        delete *it;
        objects.erase(it);
    }
}

Object *Scene::getObject(int id)
{
    for (Object *object : objects)
    {
        if (object->getID() == id)
        {
            return object;
        }
    }
    return nullptr;
}

std::string Scene::getName()
{
    return name;
}

void Scene::setName(std::string name)
{
    this->name = name;
}

std::vector<Object *> Scene::getObjects()
{
    return objects;
}