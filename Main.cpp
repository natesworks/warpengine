#include <iostream>

#include "src/Game.h"
#include "src/Components/Rectangle.h"

int main()
{
    Game game = Game(500, 500);
    game.addObject(Object(&game, Vector2(0, 0), Vector2(100, 100), Vector2(0, 0), RGB(0, 0, 255)));
    Object* object = game.getObject(0);
    object->position = Vector2(250, 250);
    Rectangle rectangle(object);
    object->addComponent(std::move(rectangle));

    while (true)
    {
        game.handleEvents();
    }
    return 0;
}