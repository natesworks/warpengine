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
    std::shared_ptr<Object> addObject(Args &&...args)
    {
        std::shared_ptr<Object> object = std::make_shared<Object>(std::forward<Args>(args)...);
        objects.push_back(object);
        return object;
    }
    template <typename T>
    std::shared_ptr<T> getObjectByType()
    {
        for (std::shared_ptr<Object> object : objects)
        {
            if (T *castObject = dynamic_cast<T *>(object))
            {
                return castObject;
            }
        }
        return nullptr;
    }
    void removeObject(std::shared_ptr<Object> object);
    std::shared_ptr<Object> getObject(int id);
    std::string getName();
    void setName(std::string name);
    const std::vector<std::shared_ptr<Object>>& getObjects() const;

private:
    std::vector<std::shared_ptr<Object>> objects;
    std::string name;
    Game *game;
};