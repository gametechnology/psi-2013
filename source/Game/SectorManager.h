/*
	Example entity for loading a model
*/

#ifndef SECTOR_MANAGER
#define SECTOR_MANAGER

#include "Engine/Scene.h"
#include "SectorTemplate.h"
#include "GalaxyMap.h"
#include "MapSector.h"
#include "Ship.h"


class SectorManager  {
public:
	SectorManager(GalaxyMap* map, Ship* ship);
	void handleMessage(unsigned int message, void* data = 0);
	void init();
	virtual ~SectorManager();
	MapSector* _mapSector;
	Ship* getShip();
private:
	GalaxyMap* _map;
	Ship* _ship;
};

#endif
