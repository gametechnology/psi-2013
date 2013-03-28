#include "ShipmapScene.h"
#include "Sprite.h"
#include "Engine/Game.h"

ShipmapScene::ShipmapScene()
{
}

ShipmapScene::~ShipmapScene()
{
}

void ShipmapScene::init()
{
	Sprite* sprite = new Sprite(this);
	sprite->setTexture(Game::driver->getTexture("../assets/shipmap/map.png"));
	sprite->setPosition(position2d<s32>(0, 0));

	addComponent(sprite);
}