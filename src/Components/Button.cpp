#include <iostream>

#include "Button.h"

Button::Button(Object *object)
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
    if (event.type == EventType::MOUSEBUTTONDOWN)
    {
        std::cout << "Button clicked\n";
    }
}

std::unique_ptr<Component> Button::clone() const
{
    return std::make_unique<Button>(*this);
}