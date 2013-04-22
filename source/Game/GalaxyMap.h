#ifndef GALAXYMAP
#define GALAXYMAP

#include "Engine/Entity.h"
#include <list>
#include <iostream>
#include "MapSector.h"

class GalaxyMap : public Entity  {
public:
	float widthMap;
	float heightMap;
	float radiusSector;
	std::list<MapSector*> sectors;

	GalaxyMap(Composite* parent);
	virtual ~GalaxyMap();
	void loadMap();
	void saveMap();
	void draw();
};

#endif