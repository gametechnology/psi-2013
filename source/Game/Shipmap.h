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

	float iconRadius, duration, savedPosX, savedPosY, playerSpeed;
	rect<s32> *boundingBoxes[5];
	rect<s32> *playerBox;
	u32 now, then;

	bool isMoving, isIntersecting, onStation, blockedE;

	int offsetX, offsetY, tileSize, iconOffset, stationNumber;

	int tiles[7][12];

public:
	Shipmap(Composite* parent);
	~Shipmap();
	void init();
	void draw();
	void update();
};