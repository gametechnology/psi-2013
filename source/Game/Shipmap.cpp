#include "Shipmap.h"
#include "Engine/Game.h"
#include <math.h>
#include "TestScene.h"
#include "Engine\Input.h"

Shipmap::Shipmap(Composite* parent):Entity(parent)
{
	bg = Game::driver->getTexture("../assets/shipmap/map.png");
	icon = Game::driver->getTexture("../assets/shipmap/icon.png");

	iconRadius = 16;
	isMoving = false;
	isIntersecting = false;

	tileSize = 64;

	playerTile.x = 2;
	playerTile.y = 3;

	offsetX = 139;
	offsetY = 72;

	const int width = 12;
	const int heigth = 7;
	int newtiles[width][heigth] = { 0, 0, 1, 1, 1, 0, 0,
									0, 0, 1, 2, 1, 0, 0,
									0, 0, 1, 0, 1, 0, 0,
									0, 0, 1, 0, 1, 1, 1,
									0, 0, 1, 0, 0, 3, 1,
									1, 1, 1, 0, 1, 1, 1,
									1, 5, 1, 0, 1, 1, 1,
									1, 0, 0, 0, 0, 4, 1,
									1, 1, 1, 0, 1, 1, 1,
									0, 0, 1, 0, 1, 0, 0,
									0, 0, 1, 6, 1, 0, 0,
									0, 0, 1, 1, 1, 0, 0 };
	for (int i = 0; i < width; i++)
		for (int j = 0; j < heigth; j++)
			tiles[i][j] = newtiles[i][j];

	posX = (playerTile.x * tileSize) + tileSize / 4;
	posY = (playerTile.y * tileSize) + tileSize / 4;
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
	Game::driver->draw2DImage(icon, rect<s32>(posX + offsetX, posY + offsetY, posX + offsetX + iconRadius * 2, posY + offsetY + iconRadius * 2), rect<s32>(0, 0, icon->getOriginalSize().Width, icon->getOriginalSize().Height));

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 7; j++)
			if (tiles[i][j] == 1)
				Game::driver->draw2DImage(icon, rect<s32>((i * tileSize) + offsetX, (j * tileSize) + offsetY, (i * tileSize) + tileSize + offsetX, (j * tileSize) + tileSize + offsetY), rect<s32>(0, 0, icon->getOriginalSize().Width, icon->getOriginalSize().Height));
}

void Shipmap::update()
{
	float playerSpeed = 0.25f;
	float newPosX = posX;
	float newPosY = posY;

	Input input;

	if (Input::KeyIsDown[irr::KEY_KEY_A])
	{
		isMoving = true;
		newPosX -= playerSpeed;
	}
    else if (Input::KeyIsDown[irr::KEY_KEY_D])
	{
		isMoving = true;
		newPosX += playerSpeed;
	}
	if (Input::KeyIsDown[irr::KEY_KEY_W])
	{
		isMoving = true;
		newPosY -= playerSpeed;
	}
    else if (Input::KeyIsDown[irr::KEY_KEY_S])
	{
		isMoving = true;
		newPosY += playerSpeed;
	}
	
	if (isMoving)
	{
		playerTile.x = (newPosX + iconRadius) / tileSize;
		playerTile.y = (newPosY + iconRadius) / tileSize;

		printf("%d, %d\n", playerTile.x, playerTile.y);

		// check the surrounding tiles
		for (int i = -1; i <= 1; i++)
		{ 
			for (int j = -1; j <= 1; j++)
			{
				// if free tile
				if (tiles[playerTile.x + i][playerTile.y + j] == 0)
					continue;
				// if station tiles
				if (tiles[playerTile.x + i][playerTile.y + j] == 2) // || 3 || 4 || 5 || 6
					continue; // do something
				
				// intersection test
				float circleDistanceX = abs((newPosX - offsetX) + iconRadius - (playerTile.x + i) * tileSize);
				float circleDistanceY = abs((newPosY - offsetY) + iconRadius - (playerTile.y + j) * tileSize);

				printf("%f, %f\n", circleDistanceX, circleDistanceY);
				
				if (circleDistanceX > (tileSize / 2) + iconRadius)
					continue;
				if (circleDistanceY > (tileSize / 2) + iconRadius)
					continue;
				
				if (circleDistanceX <= (tileSize / 2))
					isIntersecting = true;
				if (circleDistanceY <= (tileSize / 2))
					isIntersecting = true;
				
				float cornerDistanceSquared = pow(circleDistanceX - tileSize / 2, 2) + pow(circleDistanceY - tileSize / 2, 2);
				if (cornerDistanceSquared <= pow(iconRadius, 2))
					isIntersecting = true;
			}
		}
	}

	if (!isIntersecting)
	{
		posX = newPosX;
		posY = newPosY;
	}

	isMoving = isIntersecting = false;
}