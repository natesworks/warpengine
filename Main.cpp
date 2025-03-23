#include <iostream>
#include <thread>

#include "src/Game.h"
#include "src/Components/FilledRectangle.h"
#include "src/Components/FilledEllipse.h"

int main()
{
    Game game = Game(500, 500);
    game.addObject(Object(&game, Vector2(0, 0), Vector2(100, 100), 25, RGB(0, 0, 255)));
    
    Object* object = game.getObject(0);
    FilledRectangle rectangle(object);
    object->addComponent(std::move(rectangle));

    game.addObject(Object(&game, Vector2(450, 450), Vector2(100, 100), 25, RGB(255, 0, 0)));
    Object* object2 = game.getObject(1);
    FilledEllipse ellipse(object2);
    object2->addComponent(std::move(ellipse));
    game.drawer->drawAll();

    std::thread eventHandlerThread(&Game::handleEvents, &game);
    eventHandlerThread.detach();

    game.setEventHandler(EventType::MOUSEBUTTONDOWN, [&game, &object, &object2](Event e) 
    {
        std::cout << "click!\n";
        int randomX1 = rand() % game.getWindowWidth();
        int randomY1 = rand() % game.getWindowHeight();
        object->position = Vector2(randomX1, randomY1);

        int randomX2 = rand() % game.getWindowWidth();
        int randomY2 = rand() % game.getWindowHeight();
        object2->position = Vector2(randomX2, randomY2);

        game.drawer->drawAll();

    });
    while (true) {}

    return 0;
}