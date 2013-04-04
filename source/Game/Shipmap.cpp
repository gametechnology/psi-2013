#include "Shipmap.h"
#include "Engine/Game.h"
#include <math.h>
#include "TestScene.h"

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

	offsetX = 145;
	offsetY = 80;

	const int width = 12;
	const int heigth = 7;
	int newtiles[width][heigth] = { 0, 0, 1, 1, 1, 0, 0,
									0, 0, 1, 2, 1, 0, 0,
									0, 0, 1, 0, 1, 0, 0,
									0, 0, 1, 0, 1, 1, 1,
									0, 0, 1, 0, 0, 2, 1,
									1, 1, 1, 0, 1, 1, 1,
									1, 2, 1, 0, 1, 1, 1,
									1, 0, 0, 0, 0, 2, 1,
									1, 1, 1, 0, 1, 1, 1,
									0, 0, 1, 0, 1, 0, 0,
									0, 0, 1, 2, 1, 0, 0,
									0, 0, 1, 1, 1, 0, 0 };
	for (int i = 0; i < width; i++)
		for (int j = 0; j < heigth; j++)
			tiles[i][j] = newtiles[i][j];

	pos = vector2d<s32>((playerTile.x * tileSize) + offsetX, (playerTile.y * tileSize) + offsetY);
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
	Game::driver->draw2DImage(icon, vector2d<s32>(pos.X, pos.Y));
}

void Shipmap::update()
{
	float playerSpeed = 0.04f;
	/*
	if (input->rv.isKeyDown(irr::KEY_KEY_A))
	{
		isMoving = true;
		//pos.X -= playerSpeed;
	}
    else if (input->IsKeyDown(irr::KEY_KEY_D))
	{
		isMoving = true;
		//pos.X += playerSpeed;
	}
	if (input->IsKeyDown(irr::KEY_KEY_W))
	{
		isMoving = true;
		//pos.Y += playerSpeed;
	}
    else if (input->IsKeyDown(irr::KEY_KEY_S))
	{
		isMoving = true;
		//pos.Y -= playerSpeed;
	}
	*/

	if (isMoving)
	{
		playerTile.x = (pos.X - tileSize / 2) / tileSize;
		playerTile.y = (pos.Y - tileSize / 2) / tileSize;

		// check the surrounding tiles
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				// if free tile
				if (tiles[playerTile.x + i][playerTile.y + j] == 0)
					continue;
				// if station tile
				if (tiles[playerTile.x + i][playerTile.y + j] == 2)
					continue; // do something
				
				// intersection test
				float circleDistanceX = abs(pos.X + iconRadius - (playerTile.x + i) * tileSize);
				float circleDistanceY = abs(pos.Y + iconRadius - (playerTile.y + j) * tileSize);
				
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
}