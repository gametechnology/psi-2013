#ifndef SHIP_MAP
#define SHIP_MAP

#include <Engine/Core.h>
#include <Engine/GameObject.h>

#include <math.h>

#include "Stations\Station.h"
#include "GameScene.h"

class Shipmap : public GameObject
{
	void enterStation(StationType station);

	struct tilePos	{
		int x;
		int y;
	} playerTile;

	irr::gui::IGUIFont* font;

	irr::video::ITexture* bg;
	irr::video::ITexture* icon;

	irr::video::ITexture* icon_helm;
	irr::video::ITexture* icon_defense;
	irr::video::ITexture* icon_weapons;
	irr::video::ITexture* icon_navigation;
	irr::video::ITexture* icon_engine;

	float iconRadius, duration, savedPosX, savedPosY, playerSpeed;

	irr::core::rect<s32> *boundingBoxes[5];
	irr::core::rect<s32> *playerBox;
	
	irr::u32 now, then;

	bool isMoving, isIntersecting, onStation, blockedE, onOccupiedStation, stationOccupied[5];
	StationType _intersectingStation;

	int offsetX, offsetY, tileSize, iconOffset, stationNumber;
	int stationIconOffset[5];
	int stationIconDrawOffset;

	int tiles[7][12];

	Scene* _scene;
	Core* _core;
public:
	Shipmap(Core*, Scene*);
	~Shipmap();
	void onAdd();
	void init();
	void draw();
	void update();
};

#endif