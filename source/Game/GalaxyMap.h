#ifndef GALAXYMAP
#define GALAXYMAP

#include "Engine/Entity.h"
#include <vector>
#include <iostream>
#include "MapSector.h"

class GalaxyMap : public Entity  {
public:
	irr::f32 width;
	irr::f32 height;
	irr::f32 radius;

	std::vector<MapSector*> sectors;
	GalaxyMap(irr::f32 width, irr::f32 height, irr::f32 radiusSector);
	virtual ~GalaxyMap();

	virtual void onAdd();
	void createMap(int sectorCount, int minWormholes, int maxWormholes);
	void createStaticMap();
	void loadMap();
	void saveMap();
	
	void draw();
};

#endif