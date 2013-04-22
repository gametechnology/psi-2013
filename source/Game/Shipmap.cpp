#include "Shipmap.h"

Shipmap::Shipmap(Composite* parent):Entity(parent)
{
	bg = Game::driver->getTexture("../assets/shipmap/map.png");
	icon = Game::driver->getTexture("../assets/shipmap/icon.png");

	icon_helm = Game::driver->getTexture("../assets/shipmap/icon_helm.png");
	icon_defense = Game::driver->getTexture("../assets/shipmap/icon_defense.png");
	icon_weapons = Game::driver->getTexture("../assets/shipmap/icon_weapons.png");
	icon_navigation = Game::driver->getTexture("../assets/shipmap/icon_navigation.png");
	icon_engine = Game::driver->getTexture("../assets/shipmap/icon_engine.png");

	font = Game::device->getGUIEnvironment()->getBuiltInFont();

	iconRadius = (float)icon->getOriginalSize().Height/2;
	isMoving = isIntersecting = blockedE = onStation = false;

	then = Game::device->getTimer()->getTime();
	iconOffset = 30;
	stationNumber = 0;
	duration = savedPosX = savedPosY = 0.f;

	tileSize = 64;

	playerTile.x = 2;
	playerTile.y = 3;

	offsetX = 139;
	offsetY = 72;

	for (int i = 0; i < 5; i++)
		stationIconOffset[i] = icon_helm->getOriginalSize().Height;
	stationIconDrawOffset = (tileSize - stationIconOffset[0]) / 2;

	const int height = 7, width = 12;

	int newMap[height][width] = { 
		0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 2, 0, 1, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
		1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1,
		1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 
		0, 0, 0, 1, 2, 1, 1, 2, 1, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 
	};

	boundingBoxes[0] = new rect<s32>((6*tileSize)+offsetX, (1*tileSize)+offsetY, (7*tileSize)+offsetX, (2*tileSize)+offsetY);
	boundingBoxes[1] = new rect<s32>((1*tileSize)+offsetX, (3*tileSize)+offsetY, (2*tileSize)+offsetX, (4*tileSize)+offsetY);
	boundingBoxes[2] = new rect<s32>((4*tileSize)+offsetX, (5*tileSize)+offsetY, (5*tileSize)+offsetX, (6*tileSize)+offsetY);
	boundingBoxes[3] = new rect<s32>((7*tileSize)+offsetX, (5*tileSize)+offsetY, (8*tileSize)+offsetX, (6*tileSize)+offsetY);
	boundingBoxes[4] = new rect<s32>((10*tileSize)+offsetX, (3*tileSize)+offsetY, (11*tileSize)+offsetX, (4*tileSize)+offsetY);

	playerBox = new rect<s32>();

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			tiles[i][j] = newMap[i][j];

	position.X = (float)((playerTile.x * tileSize) + offsetX);
	position.Y = (float)((playerTile.y * tileSize) + offsetY + 20);
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
		// ship map
		Game::driver->draw2DImage(bg, core::position2d<s32>(0,0),
			rect<s32>(0,0,bg->getOriginalSize().Width,bg->getOriginalSize().Height),
			0, video::SColor(255,255,255,255), true);

		// helm station icon
		Game::driver->draw2DImage(icon_helm, core::position2d<s32>(boundingBoxes[4]->UpperLeftCorner.X+stationIconDrawOffset, boundingBoxes[4]->UpperLeftCorner.Y+stationIconDrawOffset),
			rect<s32>(stationIconOffset[0]-55, 0, stationIconOffset[0], icon_helm->getOriginalSize().Height),
			0, video::SColor(255,255,255,255), true);

		// defense station icon
		Game::driver->draw2DImage(icon_defense, core::position2d<s32>(boundingBoxes[2]->UpperLeftCorner.X+stationIconDrawOffset, boundingBoxes[2]->UpperLeftCorner.Y+stationIconDrawOffset),
			rect<s32>(stationIconOffset[1]-55, 0, stationIconOffset[1], icon_defense->getOriginalSize().Height),
			0, video::SColor(255,255,255,255), true);

		// weapons station icon
		Game::driver->draw2DImage(icon_weapons, core::position2d<s32>(boundingBoxes[0]->UpperLeftCorner.X+stationIconDrawOffset, boundingBoxes[0]->UpperLeftCorner.Y+stationIconDrawOffset),
			rect<s32>(stationIconOffset[2]-55, 0, stationIconOffset[2], icon_weapons->getOriginalSize().Height),
			0, video::SColor(255,255,255,255), true);

		// navigation station icon
		Game::driver->draw2DImage(icon_navigation, core::position2d<s32>(boundingBoxes[3]->UpperLeftCorner.X+stationIconDrawOffset, boundingBoxes[3]->UpperLeftCorner.Y+stationIconDrawOffset),
			rect<s32>(stationIconOffset[3]-55, 0, stationIconOffset[3], icon_navigation->getOriginalSize().Height),
			0, video::SColor(255,255,255,255), true);

		// engine station icon
		Game::driver->draw2DImage(icon_engine, core::position2d<s32>(boundingBoxes[1]->UpperLeftCorner.X+stationIconDrawOffset, boundingBoxes[1]->UpperLeftCorner.Y+stationIconDrawOffset),
			rect<s32>(stationIconOffset[4]-55, 0, stationIconOffset[4], icon_engine->getOriginalSize().Height),
			0, video::SColor(255,255,255,255), true);

		// player icon
		Game::driver->draw2DImage(icon, core::position2d<s32>((int)position.X, (int)position.Y),
			rect<s32>(iconOffset-30, 0, iconOffset, icon->getOriginalSize().Height),
			0, video::SColor(255,255,255,255), true);

		if(onStation)
		{
			if (font)
				font->draw(L"Press E to enter the Station.",
				core::rect<s32>(50,0,300,50),
				video::SColor(255,255,0,255));

		}
	}
}

void Shipmap::update()
{
	now = Game::device->getTimer()->getTime();

	playerSpeed = 1.7f;

	for(int i = 0; i < 5; i++)
		if(playerBox->isRectCollided(*boundingBoxes[i]))
			printf("Colliding with station %i \n", i);

	savedPosX = position.X;
	savedPosY = position.Y;

	playerBox->UpperLeftCorner.X = (int)position.X;
	playerBox->UpperLeftCorner.Y = (int)position.Y;
	playerBox->LowerRightCorner.X = (int)(position.X + iconRadius*2);
	playerBox->LowerRightCorner.Y = (int)(position.Y + iconRadius*2);

	playerTile.x = (int)((position.X - offsetX) / tileSize);
	playerTile.y = (int)((position.Y - offsetY) / tileSize);

	if (Game::input->isKeyboardButtonDown(irr::KEY_KEY_A))
	{
		isMoving = true;
		position.X -= playerSpeed;
	}
	else if (Game::input->isKeyboardButtonDown(irr::KEY_KEY_D))
	{
		isMoving = true;
		position.X += playerSpeed;
	}
	if (Game::input->isKeyboardButtonDown(irr::KEY_KEY_W))
	{
		isMoving = true;
		position.Y -= playerSpeed;
	}
	else if (Game::input->isKeyboardButtonDown(irr::KEY_KEY_S))
	{
		isMoving = true;
		position.Y += playerSpeed;
	}
	if (Game::input->isKeyboardButtonDown(irr::KEY_KEY_E) || Game::input->isKeyboardButtonDown(irr::KEY_KEY_F))
	{
		if(!blockedE && onStation)
		{
			//Game::getCurrentScene()->addComponent(new HelmStation(NULL));
			blockedE = !blockedE;
			//Game::getCurrentScene()->state = Game::getCurrentScene()->EXITING;
		}
	}

	if (isMoving)
	{
		int leftTile = (int)((position.X - offsetX) / tileSize);
		int rightTile = (int)(((position.X + iconRadius * 2) - offsetX) / tileSize);
		int topTile = (int)((position.Y - offsetY) / tileSize);
		int bottomTile = (int)(((position.Y + iconRadius * 2) - offsetY) / tileSize);

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
}