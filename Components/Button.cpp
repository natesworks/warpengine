#include <iostream>

#include "Button.h"

Button::Button(Object *object, std::function<void()> onClickFunction) : onClickFunction(onClickFunction)
{

}

Button::~Button()
{

}

void Button::draw(Object *object)
{

}

void Button::onEvent(Event &event)
{
    if (event.type == EventType::MOUSEBUTTONDOWN && onClickFunction)
    {
        onClickFunction();
    }
}

void Button::setOnClickFunction(std::function<void()> func)
{
    onClickFunction = func;
}

std::unique_ptr<Component> Button::clone() const
{
    return std::make_unique<Button>(*this);
}