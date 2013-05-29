#include "Shipmap.h"

using namespace irr;

Shipmap::Shipmap(Core* core, Scene* scene): _scene(scene), GameObject()
{
	_core = core;
}

Shipmap::~Shipmap()
{
}

void Shipmap::onAdd()
{
	// Assets
	bg = _core->getDriver()->getTexture("../assets/shipmap/map.png");
	icon = _core->getDriver()->getTexture("../assets/shipmap/icon.png");

	icon_helm = _core->getDriver()->getTexture("../assets/shipmap/icon_helm.png");
	icon_defense = _core->getDriver()->getTexture("../assets/shipmap/icon_defense.png");
	icon_weapons = _core->getDriver()->getTexture("../assets/shipmap/icon_weapons.png");
	icon_navigation = _core->getDriver()->getTexture("../assets/shipmap/icon_navigation.png");
	icon_engine = _core->getDriver()->getTexture("../assets/shipmap/icon_engine.png");

	font = _core->getDevice()->getGUIEnvironment()->getBuiltInFont();

	iconRadius = (float)icon->getOriginalSize().Height/2;
	isMoving = isIntersecting = blockedE = onStation = onOccupiedStation = false;

	then = _core->getDevice()->getTimer()->getTime();
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

	
	// Temporary station occupied state
	for (int i = 0; i < 5; i++)
		stationOccupied[i] = false;

	// Player starting position - should start in the middle of the plane
	_position->X = (float)((playerTile.x * tileSize) + offsetX);
	_position->Y = (float)((playerTile.y * tileSize) + offsetY + 20);
}

void Shipmap::init()
{
}

void Shipmap::draw()
{
	_core->getDriver()->draw2DImage(bg, core::position2d<s32>(0,0),
		irr::core::rect<s32>(0,0,bg->getOriginalSize().Width,bg->getOriginalSize().Height),
		0, video::SColor(255,255,255,255), true);

	_core->getDriver()->draw2DImage(icon_navigation, core::position2d<s32>(boundingBoxes[4]->UpperLeftCorner.X+stationIconDrawOffset, boundingBoxes[4]->UpperLeftCorner.Y+stationIconDrawOffset),
		irr::core::rect<s32>(stationIconOffset[0]-55, 0, stationIconOffset[0], icon_helm->getOriginalSize().Height),
		0, video::SColor(255,255,255,255), true);

	_core->getDriver()->draw2DImage(icon_weapons, core::position2d<s32>(boundingBoxes[2]->UpperLeftCorner.X+stationIconDrawOffset, boundingBoxes[2]->UpperLeftCorner.Y+stationIconDrawOffset),
		irr::core::rect<s32>(stationIconOffset[1]-55, 0, stationIconOffset[1], icon_defense->getOriginalSize().Height),
		0, video::SColor(255,255,255,255), true);

	_core->getDriver()->draw2DImage(icon_engine, core::position2d<s32>(boundingBoxes[0]->UpperLeftCorner.X+stationIconDrawOffset, boundingBoxes[0]->UpperLeftCorner.Y+stationIconDrawOffset),
		irr::core::rect<s32>(stationIconOffset[2]-55, 0, stationIconOffset[2], icon_weapons->getOriginalSize().Height),
		0, video::SColor(255,255,255,255), true);

	_core->getDriver()->draw2DImage(icon_helm, core::position2d<s32>(boundingBoxes[3]->UpperLeftCorner.X+stationIconDrawOffset, boundingBoxes[3]->UpperLeftCorner.Y+stationIconDrawOffset),
		irr::core::rect<s32>(stationIconOffset[3]-55, 0, stationIconOffset[3], icon_navigation->getOriginalSize().Height),
		0, video::SColor(255,255,255,255), true);

	_core->getDriver()->draw2DImage(icon_defense, core::position2d<s32>(boundingBoxes[1]->UpperLeftCorner.X+stationIconDrawOffset, boundingBoxes[1]->UpperLeftCorner.Y+stationIconDrawOffset),
		irr::core::rect<s32>(stationIconOffset[4]-55, 0, stationIconOffset[4], icon_engine->getOriginalSize().Height),
		0, video::SColor(255,255,255,255), true);

	// player icon
	_core->getDriver()->draw2DImage(icon, core::position2d<s32>((int)_position->X, (int)_position->Y),
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
	now = _core->getDevice()->getTimer()->getTime();

	playerSpeed = 1.7f;

	savedPosX = _position->X;
	savedPosY = _position->Y;

	playerBox->UpperLeftCorner.X = (int)_position->X;
	playerBox->UpperLeftCorner.Y = (int)_position->Y;
	playerBox->LowerRightCorner.X = (int)(_position->X + iconRadius*2);
	playerBox->LowerRightCorner.Y = (int)(_position->Y + iconRadius*2);

	playerTile.x = (int)((_position->X - offsetX) / tileSize);
	playerTile.y = (int)((_position->Y - offsetY) / tileSize);

	if (_core->getInput()->isKeyboardButtonDown(irr::KEY_KEY_A)) {
		isMoving = true;
		_position->X -= playerSpeed; 
	}

	if (_core->getInput()->isKeyboardButtonDown(irr::KEY_KEY_D)) {
		isMoving = true;
		_position->X += playerSpeed;
	}

	if (_core->getInput()->isKeyboardButtonDown(irr::KEY_KEY_W)) {
		isMoving = true;
		_position->Y -= playerSpeed;
	}

	if (_core->getInput()->isKeyboardButtonDown(irr::KEY_KEY_S)){
		isMoving = true;
		_position->Y += playerSpeed;
	}

	// TODO replace stationOccupied[i] with the hasPlayer booleans of each individual station!
	for(int i = 0; i < 5; i++) {
		if(playerBox->isRectCollided(*boundingBoxes[i])) {
			if (stationOccupied[i]) {
				onOccupiedStation = true;
				onStation = false;
			}
			else {
				onOccupiedStation = false;
				onStation = true;
			}
		}
	}

	// Enter a station
	if (onStation && (_core->getInput()->isKeyboardButtonDown(irr::KEY_KEY_E) || _core->getInput()->isKeyboardButtonDown(irr::KEY_KEY_F))) {
			enterStation(_intersectingStation);
			return;
	}
	
	if (isMoving) {
		int leftTile = (int)((_position->X - offsetX) / tileSize);
		int rightTile = (int)(((_position->X + iconRadius * 2) - offsetX) / tileSize);
		int topTile = (int)((_position->Y - offsetY) / tileSize);
		int bottomTile = (int)(((_position->Y + iconRadius * 2) - offsetY) / tileSize);

		if (tiles[topTile][leftTile] == 1 || tiles[bottomTile][leftTile] == 1 || tiles[topTile][rightTile] == 1 || tiles[bottomTile][rightTile] == 1) {
			isIntersecting = true;
		}

		// TODO replace stationOccupied[i] with the hasPlayer booleans of each individual station!
		if (tiles[topTile][leftTile] == 2 || tiles[bottomTile][leftTile] == 2 || tiles[topTile][rightTile] == 2 || tiles[bottomTile][rightTile] == 2) {
			for(int i = 0; i < 5; i++) {
				if(playerBox->isRectCollided(*boundingBoxes[i])) {
					if (stationOccupied[i]) {
						onOccupiedStation = true;
						onStation = false;
					}
					else {
						onOccupiedStation = false;
						onStation = true;
						_intersectingStation = (StationType)i;
					}
				}
			}
		} 
		else {
			onOccupiedStation = false;
			onStation = false;
		}

		if (isIntersecting) {
			_position->X = savedPosX;
			_position->Y = savedPosY;
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

	draw();
}

void Shipmap::enterStation(StationType station) {
	NetworkPacket packet(PacketType::CLIENT_SWITCH_STATION);
	packet << station;
	Network::GetInstance()->SendPacket(packet, true);

	//this->_scene->switchStation(station);
}