#include <algorithm>

#include "Scene.h"

Scene::Scene(Game *game, std::string name) : game(game), name(name) {}

void Scene::removeObject(std::shared_ptr<Object> object)
{
    for (std::shared_ptr<Object> obj : objects)
    {
        if (obj == object)
        {
            objects.erase(std::remove(objects.begin(), objects.end(), obj), objects.end());
            return;
        }
    }
}

std::shared_ptr<Object> Scene::getObject(int id)
{
    for (std::shared_ptr<Object> object : objects)
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

const std::vector<std::shared_ptr<Object>>& Scene::getObjects() const
{
    return objects;
}