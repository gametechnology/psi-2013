#pragma once
#include "Engine\Entity.h"
#include "Shipmap.h"

class Shipmap :
	public Entity
{
private:
	video::ITexture* bg;
	video::ITexture* icon;

	vector2d<s32> pos;
	float iconRadius;
	bool isMoving;
	bool isIntersecting;
	struct tilePos	{
		int x;
		int y;
	} playerTile;

	int offsetX;
	int offsetY;
	int tileSize;

	int tiles[12][7];

public:
	Shipmap(Composite* parent);
	~Shipmap();
	void init();
	void draw();
	void update();
};