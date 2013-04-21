#pragma once
#include "Engine\Entity.h"
#include "Shipmap.h"
#include "Engine/Game.h"
#include <math.h>

class Shipmap : public Entity
{
	struct tilePos	{
		int x;
		int y;
	} playerTile;

	gui::IGUIFont* font;

	video::ITexture* bg;
	video::ITexture* icon;

	video::ITexture* icon_helm;
	video::ITexture* icon_defense;
	video::ITexture* icon_weapons;
	video::ITexture* icon_navigation;
	video::ITexture* icon_engine;

	float iconRadius, duration, savedPosX, savedPosY, playerSpeed;
	irr::core::rect<s32> *boundingBoxes[5];
	irr::core::rect<s32> *playerBox;
	u32 now, then;

	bool isMoving, isIntersecting, onStation, blockedE, onOccupiedStation, stationOccupied[5];

	int offsetX, offsetY, tileSize, iconOffset, stationNumber;
	int stationIconOffset[5];
	int stationIconDrawOffset;

	int tiles[7][12];

public:
	Shipmap(Composite* parent);
	~Shipmap();
	void init();
	void draw();
	void update();
};