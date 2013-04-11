/*
	Example entity for loading a model
*/

#ifndef SECTOR_MANAGER
#define SECTOR_MANAGER

#include "Engine/Scene.h"
#include "SectorTemplate.h"
#include "GalaxyMap.h"
#include "MapSector.h"


class SectorManager  {
public:
	SectorManager(GalaxyMap* map);
	void handleMessage(unsigned int message, void* data = 0);
	void init();
	virtual ~SectorManager();
	MapSector* _mapSector;
private:
	GalaxyMap* _map;
};

#endif
