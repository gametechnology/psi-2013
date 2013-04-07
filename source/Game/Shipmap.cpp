#include "Shipmap.h"
#include "Engine/Game.h"
#include <math.h>
#include "TestScene.h"
#include "Engine\Input.h"

Shipmap::Shipmap(Composite* parent):Entity(parent)
{
	bg = Game::driver->getTexture("../assets/shipmap/map.png");
	icon = Game::driver->getTexture("../assets/shipmap/icon.png");

	iconRadius = 25;
	isMoving = false;
	isIntersecting = false;

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
	
	posX = (playerTile.x * tileSize) + offsetX;
	posY = (playerTile.y * tileSize) + offsetY;
	//posX = (playerTile.x * tileSize) + tileSize / 4;
	//posY = (playerTile.y * tileSize) + tileSize / 4;
	//pos = position2d<s32>((playerTile.x * tileSize) + offsetX, (playerTile.y * tileSize) + offsetY);
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

	Game::driver->draw2DImage(bg, rect<s32>(0,0,1060,600), rect<s32>(0,0,bg->getOriginalSize().Width,bg->getOriginalSize().Height));
	Game::driver->draw2DImage(icon, vector2d<s32>(posX, posY));
	//Game::driver->draw2DImage(icon, rect<s32>(posX + offsetX, posY + offsetY, posX + offsetX + iconRadius * 2, posY + offsetY + iconRadius * 2), rect<s32>(0, 0, icon->getOriginalSize().Width, icon->getOriginalSize().Height));

	/*for (int i = 0; i < 12; i++)
		for (int j = 0; j < 7; j++)
			if (tiles[i][j] == 1)
				Game::driver->draw2DImage(icon, rect<s32>((i * tileSize) + offsetX, (j * tileSize) + offsetY, (i * tileSize) + tileSize + offsetX, (j * tileSize) + tileSize + offsetY), rect<s32>(0, 0, icon->getOriginalSize().Width, icon->getOriginalSize().Height));*/
}

void Shipmap::update()
{
	float playerSpeed = 1.0f;
	float savedPosX = posX;
	float savedPosY = posY;

	Input input;

	playerTile.x = (posX - offsetX) / tileSize;
	playerTile.y = (posY - offsetY) / tileSize;

	if (Input::KeyIsDown[irr::KEY_KEY_A])
	{
		isMoving = true;
		posX -= playerSpeed;
	}
    else if (Input::KeyIsDown[irr::KEY_KEY_D])
	{
		isMoving = true;
		posX += playerSpeed;
	}
	if (Input::KeyIsDown[irr::KEY_KEY_W])
	{
		isMoving = true;
		posY -= playerSpeed;
	}
    else if (Input::KeyIsDown[irr::KEY_KEY_S])
	{
		isMoving = true;
		posY += playerSpeed;
	}
	if (Input::KeyIsDown[irr::KEY_KEY_E] || Input::KeyIsDown[irr::KEY_KEY_F])
	{
		// enter station routine on E or F
	}
	
	if (isMoving)
	{
		int leftTile = (posX - offsetX) / tileSize;
		int rightTile = ((posX + iconRadius * 2) - offsetX) / tileSize;
		int topTile = (posY - offsetY) / tileSize;
		int bottomTile = ((posY + iconRadius * 2) - offsetY) / tileSize;

		bool collision = false;

		if (tiles[topTile][leftTile] == 1 || tiles[bottomTile][leftTile] == 1)
		{
			collision = true;
		}
		if (tiles[topTile][rightTile] == 1 || tiles[bottomTile][rightTile] == 1)
		{
			collision = true;
		}
		if (tiles[topTile][leftTile] == 1 || tiles[topTile][rightTile] == 1)
		{
			collision = true;
		}
		if (tiles[bottomTile][leftTile] == 1 || tiles[bottomTile][rightTile] == 1)
		{
			collision = true;
		}

		if (collision)
		{
			posX = savedPosX;
			posY = savedPosY;
		}
	}

	isMoving = isIntersecting = false;
}