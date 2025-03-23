#include <iostream>
#include <thread>

#include "src/Game.h"
#include "src/Types/Object.h"
#include "src/Components/Rectangle.h"
#include "src/Components/FilledRectangle.h"
#include "src/Components/Ellipse.h"
#include "src/Components/FilledEllipse.h"
#include "src/Components/Button.h"

void onClick(Game& game, Object& object)
{
    int randomX = rand() % game.getWindowWidth();
    int randomY = rand() % game.getWindowHeight();
    object.setPosition(Vector2(randomX, randomY));
}

int main()
{
    Game game = Game(960, 540, "Portal 3");
    game.addObject(Object(&game, Vector2(0, 0), Vector2(100, 100), 25, RGB(0, 0, 255)));
    Object* object = game.getObject(0);
    FilledRectangle rectangle(object);
    object->addComponent(std::move(rectangle));
    Button button(object, [&game, &object]() { onClick(game, *object); });
    object->addComponent(std::move(button));
    Rectangle hitbox(object);
    object->addComponent(std::move(hitbox));

    game.addObject(Object(&game, Vector2(450, 450), Vector2(100, 100), 25, RGB(255, 0, 0)));
    Object* object2 = game.getObject(1);
    FilledEllipse ellipse(object2);
    object2->addComponent(std::move(ellipse));
    Button button2(object2, [&game, &object2]() { onClick(game, *object2); });
    object2->addComponent(std::move(button2));
    Rectangle hitbox2(object);
    //object2->addComponent(std::move(hitbox2));

    game.start();

    while (true) {}

    return 0;
}