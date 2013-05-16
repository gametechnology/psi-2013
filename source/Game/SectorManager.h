#ifndef SECTOR_MANAGER
#define SECTOR_MANAGER

#include "Engine/Component.h"
#include "SectorTemplate.h"
#include "GalaxyMap.h"
#include "MapSector.h"
#include "Ship.h"


class SectorManager : public Component {
public:
	SectorManager(GalaxyMap* map,Ship* ship);
	void handleMessage(unsigned int message, void* data = 0);
	void onAdd();
	virtual ~SectorManager();
	MapSector* _mapSector;
	char* activeSceneName;
	Ship* getShip();
private:
	GalaxyMap* _map;
	Ship* _ship;
};

#endif
