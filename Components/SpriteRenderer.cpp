#include <string>

#include "SpriteRenderer.h"
#include "../Rendering/Drawer.h"
#include "../Types/Vector2.h"

SpriteRenderer::SpriteRenderer(Object *object, std::string image) : image(image)
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::draw(Object *object)
{
    object->game->drawer->drawSprite(image, object->getPosition(), object->getScale(), object->color);
}