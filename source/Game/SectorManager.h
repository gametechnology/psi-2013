#ifndef SECTOR_MANAGER
#define SECTOR_MANAGER

#include <Engine/Composite.h>
#include <algorithm>

#include "GalaxyMap.h"
#include "MapSector.h"
#include "Ship.h"
#include "Messages.h"
#include "AsteroidSector.h"
#include "NebulaSector.h"
#include "SectorHomeBase.h"
#include "BaseSector.h"

class GameScene;

class SectorManager : public Composite
{
public:
	SectorManager(GameScene*, Core*, GalaxyMap*, Ship*);
	virtual ~SectorManager();

	virtual void init();
	virtual void update();

	virtual void handleMessage(unsigned int message, void* data = 0);

	Ship* getShip() { return _ship; };
private:
	GalaxyMap* _map;
	Ship* _ship;
	MapSector* _mapSector;
	SectorTemplate* _activeSector;
	GameScene* _gameScene;
	Core* _core;
};

#endif
