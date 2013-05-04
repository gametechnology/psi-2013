#include "Shipmap.h"

Shipmap::Shipmap():Entity()
{
	
}

Shipmap::~Shipmap()
{
}

void Shipmap::onAdd()
{
	// Assets
	bg = game->driver->getTexture("../assets/shipmap/map.png");
	icon = game->driver->getTexture("../assets/shipmap/icon.png");

	icon_helm = game->driver->getTexture("../assets/shipmap/icon_helm.png");
	icon_defense = game->driver->getTexture("../assets/shipmap/icon_defense.png");
	icon_weapons = game->driver->getTexture("../assets/shipmap/icon_weapons.png");
	icon_navigation = game->driver->getTexture("../assets/shipmap/icon_navigation.png");
	icon_engine = game->driver->getTexture("../assets/shipmap/icon_engine.png");

	font = game->device->getGUIEnvironment()->getBuiltInFont();

	iconRadius = (float)icon->getOriginalSize().Height/2;
	isMoving = isIntersecting = blockedE = onStation = onOccupiedStation = false;

	then = game->device->getTimer()->getTime();
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

	// Ship tile map
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
	
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			tiles[i][j] = newMap[i][j];

	// Stations bounding boxes
	boundingBoxes[2] = new irr::core::rect<s32>((6*tileSize)+offsetX, (1*tileSize)+offsetY, (7*tileSize)+offsetX, (2*tileSize)+offsetY);
	boundingBoxes[0] = new irr::core::rect<s32>((1*tileSize)+offsetX, (3*tileSize)+offsetY, (2*tileSize)+offsetX, (4*tileSize)+offsetY);
	boundingBoxes[1] = new irr::core::rect<s32>((4*tileSize)+offsetX, (5*tileSize)+offsetY, (5*tileSize)+offsetX, (6*tileSize)+offsetY);
	boundingBoxes[4] = new irr::core::rect<s32>((7*tileSize)+offsetX, (5*tileSize)+offsetY, (8*tileSize)+offsetX, (6*tileSize)+offsetY);
	boundingBoxes[3] = new irr::core::rect<s32>((10*tileSize)+offsetX, (3*tileSize)+offsetY, (11*tileSize)+offsetX, (4*tileSize)+offsetY);

	playerBox = new irr::core::rect<s32>();

	/*
	* Temporary station occupied state
	* TODO remove this and replace it with each individual station's hasPlayer boolean when implementing!
	*/
	for (int i = 0; i < 5; i++)
		stationOccupied[i] = false;

	// Player starting position
	this->transform->position->X = (float)((playerTile.x * tileSize) + offsetX);
	this->transform->position->Y = (float)((playerTile.y * tileSize) + offsetY + 20);
}

void Shipmap::init()
{
}

void Shipmap::draw()
{
	Entity::draw();

	// ship map
	game->driver->draw2DImage(bg, core::position2d<s32>(0,0),
		irr::core::rect<s32>(0,0,bg->getOriginalSize().Width,bg->getOriginalSize().Height),
		0, video::SColor(255,255,255,255), true);

	// helm station icon
	game->driver->draw2DImage(icon_helm, core::position2d<s32>(boundingBoxes[4]->UpperLeftCorner.X+stationIconDrawOffset, boundingBoxes[4]->UpperLeftCorner.Y+stationIconDrawOffset),
		irr::core::rect<s32>(stationIconOffset[0]-55, 0, stationIconOffset[0], icon_helm->getOriginalSize().Height),
		0, video::SColor(255,255,255,255), true);

	// defense station icon
	game->driver->draw2DImage(icon_defense, core::position2d<s32>(boundingBoxes[2]->UpperLeftCorner.X+stationIconDrawOffset, boundingBoxes[2]->UpperLeftCorner.Y+stationIconDrawOffset),
		irr::core::rect<s32>(stationIconOffset[1]-55, 0, stationIconOffset[1], icon_defense->getOriginalSize().Height),
		0, video::SColor(255,255,255,255), true);

	// weapons station icon
	game->driver->draw2DImage(icon_weapons, core::position2d<s32>(boundingBoxes[0]->UpperLeftCorner.X+stationIconDrawOffset, boundingBoxes[0]->UpperLeftCorner.Y+stationIconDrawOffset),
		irr::core::rect<s32>(stationIconOffset[2]-55, 0, stationIconOffset[2], icon_weapons->getOriginalSize().Height),
		0, video::SColor(255,255,255,255), true);

	// navigation station icon
	game->driver->draw2DImage(icon_navigation, core::position2d<s32>(boundingBoxes[3]->UpperLeftCorner.X+stationIconDrawOffset, boundingBoxes[3]->UpperLeftCorner.Y+stationIconDrawOffset),
		irr::core::rect<s32>(stationIconOffset[3]-55, 0, stationIconOffset[3], icon_navigation->getOriginalSize().Height),
		0, video::SColor(255,255,255,255), true);

	// engine station icon
	game->driver->draw2DImage(icon_engine, core::position2d<s32>(boundingBoxes[1]->UpperLeftCorner.X+stationIconDrawOffset, boundingBoxes[1]->UpperLeftCorner.Y+stationIconDrawOffset),
		irr::core::rect<s32>(stationIconOffset[4]-55, 0, stationIconOffset[4], icon_engine->getOriginalSize().Height),
		0, video::SColor(255,255,255,255), true);

	// player icon
	game->driver->draw2DImage(icon, core::position2d<s32>((int)this->transform->position->X, (int)this->transform->position->Y),
		irr::core::rect<s32>(iconOffset-30, 0, iconOffset, icon->getOriginalSize().Height),
		0, video::SColor(255,255,255,255), true);

	if(onStation)
	{
		if (font)
			font->draw(L"Press E to enter the Station.",
			core::rect<s32>(50,0,300,50),
			video::SColor(255,255,0,255));
	}
	else if (onOccupiedStation)
	{
		if (font)
			font->draw(L"This station is occupied and cannot be entered at the moment",
			core::rect<s32>(250,0,500,50),
			video::SColor(255,255,0,255));
	}
}

void Shipmap::update()
{
	now = game->device->getTimer()->getTime();

	playerSpeed = 1.7f;

	savedPosX = this->transform->position->X;
	savedPosY = this->transform->position->Y;

	playerBox->UpperLeftCorner.X = (int)this->transform->position->X;
	playerBox->UpperLeftCorner.Y = (int)this->transform->position->Y;
	playerBox->LowerRightCorner.X = (int)(this->transform->position->X + iconRadius*2);
	playerBox->LowerRightCorner.Y = (int)(this->transform->position->Y + iconRadius*2);

	playerTile.x = (int)((this->transform->position->X - offsetX) / tileSize);
	playerTile.y = (int)((this->transform->position->Y - offsetY) / tileSize);

	if (game->input->isKeyboardButtonDown(irr::KEY_KEY_A))
	{
		isMoving = true;
		this->transform->position->X -= playerSpeed;
	}
	else if (game->input->isKeyboardButtonDown(irr::KEY_KEY_D))
	{
		isMoving = true;
		this->transform->position->X += playerSpeed;
	}
	if (game->input->isKeyboardButtonDown(irr::KEY_KEY_W))
	{
		isMoving = true;
		this->transform->position->Y -= playerSpeed;
	}
	else if (game->input->isKeyboardButtonDown(irr::KEY_KEY_S))
	{
		isMoving = true;
		this->transform->position->Y += playerSpeed;
	}

	// TODO remove this when implementing stations - it's merely for testing purposes to see if station occupied state works
	if (game->input->isKeyboardButtonPressed(irr::KEY_KEY_0))
	{
		stationOccupied[0] = !stationOccupied[0];
	}
	if (game->input->isKeyboardButtonPressed(irr::KEY_KEY_1))
	{
		stationOccupied[1] = !stationOccupied[1];
	}
	if (game->input->isKeyboardButtonPressed(irr::KEY_KEY_2))
	{
		stationOccupied[2] = !stationOccupied[2];
	}
	if (game->input->isKeyboardButtonPressed(irr::KEY_KEY_3))
	{
		stationOccupied[3] = !stationOccupied[3];
	}
	if (game->input->isKeyboardButtonPressed(irr::KEY_KEY_4))
	{
		stationOccupied[4] = !stationOccupied[4];
	}
	if (game->input->isKeyboardButtonPressed(irr::KEY_KEY_5))
	{
		stationOccupied[5] = !stationOccupied[5];
	}

	// TODO replace stationOccupied[i] with the hasPlayer booleans of each individual station!
	for(int i = 0; i < 5; i++)
	{
		if(playerBox->isRectCollided(*boundingBoxes[i]))
		{
			if (stationOccupied[i])
			{
				onOccupiedStation = true;
				onStation = false;
			}
			else
			{
				onOccupiedStation = false;
				onStation = true;
			}
		}
	}

	// Enter a station
	// TODO implement with stations, enter the correct station on pressing E by checking position against boundingboxes
	if (onStation && (game->input->isKeyboardButtonDown(irr::KEY_KEY_E) || game->input->isKeyboardButtonDown(irr::KEY_KEY_F)))
	{
			enterStation(_intersectingStation);
			//Game::getCurrentScene()->addComponent(new HelmStation(NULL));
			//Game::getCurrentScene()->state = Game::getCurrentScene()->EXITING;
	}
	

	if (isMoving)
	{
		int leftTile = (int)((this->transform->position->X - offsetX) / tileSize);
		int rightTile = (int)(((this->transform->position->X + iconRadius * 2) - offsetX) / tileSize);
		int topTile = (int)((this->transform->position->Y - offsetY) / tileSize);
		int bottomTile = (int)(((this->transform->position->Y + iconRadius * 2) - offsetY) / tileSize);

		if (tiles[topTile][leftTile] == 1 || tiles[bottomTile][leftTile] == 1 || tiles[topTile][rightTile] == 1 || tiles[bottomTile][rightTile] == 1)
		{
			isIntersecting = true;
		}

		// TODO replace stationOccupied[i] with the hasPlayer booleans of each individual station!
		if (tiles[topTile][leftTile] == 2 || tiles[bottomTile][leftTile] == 2 || tiles[topTile][rightTile] == 2 || tiles[bottomTile][rightTile] == 2)
		{
			for(int i = 0; i < 5; i++)
			{
				if(playerBox->isRectCollided(*boundingBoxes[i]))
				{
					if (stationOccupied[i])
					{
						onOccupiedStation = true;
						onStation = false;
					}
					else
					{
						onOccupiedStation = false;
						onStation = true;
						_intersectingStation = (StationType)i;
					}
				}
			}
		} 
		else 
		{
			onOccupiedStation = false;
			onStation = false;
		}

		if (isIntersecting)
		{
			this->transform->position->X = savedPosX;
			this->transform->position->Y = savedPosY;
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

void Shipmap::enterStation(StationType station)
{
	printf("Enter station with station %i \n", station);

	switch(station)
	{
		case StationType::ST_DEFENCE:
			break;
		case StationType::ST_HELM:
			break;
		case StationType::ST_NAVIGATION:
			break;
		case StationType::ST_POWER:
			break;
		case StationType::ST_WEAPON:
			break;
	}
}