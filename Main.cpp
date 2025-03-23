#include <iostream>
#include <thread>

#include "src/Game.h"
#include "src/Components/FilledRectangle.h"
#include "src/Components/FilledEllipse.h"
#include "src/Components/Button.h"

int main()
{
    Game game = Game(500, 500);
    game.addObject(Object(&game, Vector2(0, 0), Vector2(100, 100), 25, RGB(0, 0, 255)));
    Object* object = game.getObject(0);
    FilledRectangle rectangle(object);
    object->addComponent(std::move(rectangle));
    Button button(object);
    object->addComponent(std::move(button));

    game.addObject(Object(&game, Vector2(450, 450), Vector2(100, 100), 25, RGB(255, 0, 0)));
    Object* object2 = game.getObject(1);
    FilledEllipse ellipse(object2);
    object2->addComponent(std::move(ellipse));

    game.start();

    while (true) {}

    return 0;
}