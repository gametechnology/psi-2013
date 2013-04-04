#include "Shipmap.h"
#include "Sprite.h"
#include "Engine/Game.h"

Shipmap::Shipmap(Composite* parent):Entity(parent)
{
	bg = Game::driver->getTexture("../assets/shipmap/map.png");
}

Shipmap::~Shipmap()
{
}

void Shipmap::init()
{
}

void Shipmap::draw()
{
	Entity::draw();

	Game::driver->draw2DImage(bg, rect<s32>(0,0,1280,720), rect<s32>(0,0,bg->getOriginalSize().Width,bg->getOriginalSize().Height));
}