/*
	Example entity for loading a model
*/

#ifndef SECTOR_MANAGER
#define SECTOR_MANAGER

#include "Engine/Scene.h"
#include "SectorTemplate.h"
#include "GalaxyMap.h"
#include "MapSector.h"


class SectorManager : public Scene  {
public:
	SectorManager(GalaxyMap* map);
	void SectorManager::handleMessage(unsigned int message, void* data = 0);
	void SectorManager::init();
	virtual ~SectorManager();
private:
	SectorTemplate *_currentSector;
	GalaxyMap* _map;
	MapSector* _mapSector;
};

#endif
