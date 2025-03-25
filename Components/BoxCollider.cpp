#include <iostream>

#include "BoxCollider.h"

BoxCollider::BoxCollider(Object *object, std::function<void()> onClickFunction)
{

}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::draw(Object *object)
{

}

void BoxCollider::onEvent(Event &event)
{

}

void BoxCollider::setOnTriggerEnterFunction(std::function<void()> func)
{
    onTriggerEnter = func;
}

std::unique_ptr<Component> BoxCollider::clone() const
{
    return std::make_unique<BoxCollider>(*this);
}