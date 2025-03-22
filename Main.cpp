#include <iostream>
#include <thread>

#include "src/Game.h"
#include "src/Components/Rectangle.h"
#include "src/Components/FilledRectangle.h"
#include "src/Components/Ellipse.h"
#include "src/Components/FilledEllipse.h"

int main()
{
    Game game = Game(500, 500);
    game.addObject(Object(&game, Vector2(0, 0), Vector2(100, 100), Vector2(0, 0), RGB(0, 0, 255)));
    
    Object* object = game.getObject(0);
    FilledRectangle rectangle(object);
    object->addComponent(std::move(rectangle));

    game.addObject(Object(&game, Vector2(450, 450), Vector2(100, 100), Vector2(0, 0), RGB(255, 0, 0)));
    Object* object2 = game.getObject(1);
    FilledEllipse ellipse(object2);
    object2->addComponent(std::move(ellipse));
    game.drawer->drawAll();

    std::thread eventHandlerThread(&Game::handleEvents, &game);
    eventHandlerThread.detach();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    object->position = Vector2(250, 250);
    game.drawer->drawAll();
    while (true) {}

    return 0;
}