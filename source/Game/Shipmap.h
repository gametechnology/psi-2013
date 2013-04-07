#pragma once
#include "Engine\Entity.h"
#include "Shipmap.h"

class Shipmap : public Entity
{
	struct tilePos	{
		int x;
		int y;
	} playerTile;

	gui::IGUIFont* font;

	video::ITexture* bg;
	video::ITexture* icon;

	float iconRadius, duration;

	u32 now, then;

	bool isMoving, isIntersecting, onStation, blockedE;

	int offsetX, offsetY, tileSize, iconOffset;

	int tiles[7][12];

public:
	Shipmap(Composite* parent);
	~Shipmap();
	void init();
	void draw();
	void update();
};