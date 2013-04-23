#ifndef SECTOR_MANAGER
#define SECTOR_MANAGER

#include "Engine/Component.h"
#include "SectorTemplate.h"
#include "GalaxyMap.h"
#include "MapSector.h"


class SectorManager : public Component {
public:
	SectorManager(GalaxyMap* map);
	void handleMessage(unsigned int message, void* data = 0);
	void onAdd();
	virtual ~SectorManager();
	MapSector* _mapSector;
	char* activeSceneName;
private:
	GalaxyMap* _map;
};

#endif
