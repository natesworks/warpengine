#include "Text.h"
#include "../Rendering/Drawer.h"
#include "../Types/Vector2.h"
#include <string>

Text::Text(Object *object, std::string text, std::string font, int fontSize) : text(text), font(font), fontSize(fontSize)
{
    draw(object);
}

Text::~Text()
{

}

void Text::draw(Object *object)
{
    object->game->drawer->drawText(text, font, fontSize, object->getPosition(), object->getScale(), object->color);
}