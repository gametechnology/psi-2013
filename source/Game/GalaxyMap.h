#ifndef GALAXYMAP
#define GALAXYMAP

#include <Engine/Composite.h>
#include <Engine/GameObject.h>
#include <Engine/Core.h>

#include <vector>
#include <iostream>

#include "MapSector.h"
#include "MapGenerator.h"


class GalaxyMap : public GameObject
{
public:
	irr::f32 width;
	irr::f32 height;
	irr::f32 radius;	

	GalaxyMap(Core* core, irr::f32 width, irr::f32 height, irr::f32 radiusSector);
	virtual ~GalaxyMap();

	virtual void onAdd();
	void createMap(int sectorCount, int minWormholes, int maxWormholes);
	void createStaticMap();
	void loadMap();
	void saveMap();
	
	virtual void update();
	virtual void handleMessage(unsigned int, void* data = 0) { };

	std::list<MapSector*>* getSectors() { return &sectors; };
private:
	Core* _core;
	std::list<MapSector*> sectors;
};

#endif