#pragma once

#include <functional>

#include "../../Types/Component.h"
#include "../../Types/Object.h"

class Button : public Component
{
public:
    Button(Object *object, std::function<void()> onClickFunction = []() {});
    ~Button();
    void onEvent(Event &event) override;
    void setOnClickFunction(std::function<void()> func);

private:
    std::function<void()> onClickFunction;
    Object* object;
};