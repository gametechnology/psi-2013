#pragma once
#include "Engine\Entity.h"
#include "Shipmap.h"

class Shipmap :
	public Entity
{
private:
	video::ITexture* bg;
	video::ITexture* icon;

	int posX;
	int posY;
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

	int tiles[7][12];

public:
	Shipmap(Composite* parent);
	~Shipmap();
	void init();
	void draw();
	void update();
};