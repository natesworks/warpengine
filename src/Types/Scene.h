#pragma once

#include <vector>
#include <string>

#include "Object.h"

class Scene
{
public:
    Scene(Game *game, std::string name);
    ~Scene() = default;

    template <typename... Args>
    Object *addObject(Args &&...args)
    {
        Object *object = new Object(game, std::forward<Args>(args)...);
        objects.push_back(object);
        return object;
    }
    template <typename T>
    T *getObjectByType()
    {
        for (Object *object : objects)
        {
            if (T *castObject = dynamic_cast<T *>(object))
            {
                return castObject;
            }
        }
        return nullptr;
    }
    void removeObject(Object *object);
    Object *getObject(int id);
    std::string getName();
    void setName(std::string name);
    std::vector<Object *> getObjects();

private:
    std::vector<Object *> objects;
    std::string name;
    Game *game;
};