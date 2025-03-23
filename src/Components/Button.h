#pragma once

#include <functional>

#include "../Types/Component.h"
#include "../Types/Object.h"

class Button : public Component
{
public:
    Button(Object *object, std::function<void()> onClickFunction = []() {});
    ~Button();
    void draw(Object *object) override;
    void onEvent(Event &event) override;
    void setOnClickFunction(std::function<void()> func);

    std::unique_ptr<Component> clone() const override;

private:
    std::function<void()> onClickFunction;
};