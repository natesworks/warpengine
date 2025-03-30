#pragma once

#include "../Types/Component.h"
#include "../Types/Object.h"
#include "../Types/Event.h"

class Text : public Component
{
public:
    Text(Object *object, std::string text, std::string font, int fontSize);
    ~Text();
    void draw(Object *object) override;
    void onEvent(Event &event) override {}
private:
    std::string font;
    std::string text;
    int fontSize;
};