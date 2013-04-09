#include "Shipmap.h"
#include "Engine/Game.h"
#include <math.h>
#include "TestScene.h"

Shipmap::Shipmap(Composite* parent):Entity(parent)
{
	bg = Game::driver->getTexture("../assets/shipmap/map.png");
	icon = Game::driver->getTexture("../assets/shipmap/icon.png");

	font = Game::device->getGUIEnvironment()->getBuiltInFont();

	iconRadius = icon->getOriginalSize().Height/2;
	isMoving = isIntersecting = blockedE = onStation = false;

	then = Game::device->getTimer()->getTime();
	iconOffset = 30;
	duration = 0;

	tileSize = 64;

	playerTile.x = 2;
	playerTile.y = 3;

	offsetX = 139;
	offsetY = 72;

	const int height = 7;
	const int width = 12;
	int newMap[height][width] = { 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 2, 0, 1, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
		1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1,
		1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 
		0, 0, 0, 1, 2, 1, 1, 2, 1, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 };


	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			tiles[i][j] = newMap[i][j];

	position.X = (playerTile.x * tileSize) + offsetX;
	position.Y = (playerTile.y * tileSize) + offsetY;
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
	/*
	* Obscene dirty hack to stop this scene from drawing when there is a station loaded.
	* TODO Revamp the engine so it can change scenes in a normal way.Obscene dirty hack to stop this scene from drawing when there is a station loaded.
	*/
	if(!blockedE)
	{
		Game::driver->draw2DImage(bg, core::position2d<s32>(0,0),
			rect<s32>(0,0,bg->getOriginalSize().Width,bg->getOriginalSize().Height),
			0, video::SColor(255,255,255,255), true);

		Game::driver->draw2DImage(icon, core::position2d<s32>(position.X, position.Y),
			rect<s32>(iconOffset-30, 0, iconOffset, icon->getOriginalSize().Height),
			0, video::SColor(255,255,255,255), true);

		if(onStation)
		{
			if (font)
				font->draw(L"Press E to enter the Station.",
				core::rect<s32>(0,0,300,50),
				video::SColor(255,255,0,255));

		}
	}
}

void Shipmap::update()
{
	/*
	now = Game::device->getTimer()->getTime();

	float playerSpeed = 0.7f;
	float savedPosX = position.X;
	float savedPosY = position.Y;

	Input input;

	playerTile.x = (position.X - offsetX) / tileSize;
	playerTile.y = (position.Y - offsetY) / tileSize;

	if (Input::KeyIsDown[irr::KEY_KEY_A])
	{
		isMoving = true;
		position.X -= playerSpeed;
	}
	else if (Input::KeyIsDown[irr::KEY_KEY_D])
	{
		isMoving = true;
		position.X += playerSpeed;
	}
	if (Input::KeyIsDown[irr::KEY_KEY_W])
	{
		isMoving = true;
		position.Y -= playerSpeed;
	}
	else if (Input::KeyIsDown[irr::KEY_KEY_S])
	{
		isMoving = true;
		position.Y += playerSpeed;
	}
	if (Input::KeyIsDown[irr::KEY_KEY_E] || Input::KeyIsDown[irr::KEY_KEY_F])
	{
		if(!blockedE && onStation)
		{
			Game::getCurrentScene()->addComponent(new HelmStation(NULL));
			blockedE = !blockedE;
			Game::getCurrentScene()->state = Game::getCurrentScene()->EXITING;
		}
	}

	if (isMoving)
	{
		int leftTile = (position.X - offsetX) / tileSize;
		int rightTile = ((position.X + iconRadius * 2) - offsetX) / tileSize;
		int topTile = (position.Y - offsetY) / tileSize;
		int bottomTile = ((position.Y + iconRadius * 2) - offsetY) / tileSize;

		if (tiles[topTile][leftTile] == 1 || tiles[bottomTile][leftTile] == 1 || tiles[topTile][rightTile] == 1 || tiles[bottomTile][rightTile] == 1)
		{
			isIntersecting = true;
		}

		if (tiles[topTile][leftTile] == 2 || tiles[bottomTile][leftTile] == 2 || tiles[topTile][rightTile] == 2 || tiles[bottomTile][rightTile] == 2)
		{
			onStation = true;
		} 
		else 
		{
			onStation = false;
		}

		if (isIntersecting)
		{
			position.X = savedPosX;
			position.Y = savedPosY;
		}
	}

	isMoving = isIntersecting = false;

	const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds

	duration += frameDeltaTime;

	if(duration > 0.5f) {
		iconOffset += 30;
		if(iconOffset >= 120)
			iconOffset = 30;
		duration = 0;
	}

	then = now;
	*/
}