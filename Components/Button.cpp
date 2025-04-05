#include <iostream>

#include "Button.h"

Button::Button(Object *object, std::function<void()> onClickFunction) : onClickFunction(onClickFunction), object(object)
{

}

Button::~Button()
{

}

void Button::onEvent(Event &event)
{
    if (event.type == EventType::MOUSEBUTTONDOWN && onClickFunction && object->isOverlapping(event.mousePosition))
    {
        onClickFunction();
    }
}

void Button::setOnClickFunction(std::function<void()> func)
{
    onClickFunction = func;
}