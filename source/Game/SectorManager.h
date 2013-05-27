#ifndef SECTOR_MANAGER
#define SECTOR_MANAGER

#include <Engine/Component.h>
#include "SectorTemplate.h"
#include "GalaxyMap.h"
#include "MapSector.h"
#include "Ship.h"

class SectorManager : public Component
{
public:
	SectorManager(GalaxyMap* map, Ship* ship);
	virtual ~SectorManager();
	
	virtual void init();
	virtual void update();

	virtual void handleMessage(unsigned int message, void* data = 0);

	Ship* getShip() { return _ship; };
private:
	GalaxyMap* _map;
	Ship* _ship;
	MapSector* _mapSector;
	char* _activeSceneName;	
};

#endif
