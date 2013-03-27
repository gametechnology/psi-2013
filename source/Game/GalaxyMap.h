#ifndef GALAXYMAP
#define GALAXYMAP

#include "Engine/Entity.h"
#include <list>
class MapSector;
class GalaxyMap : public Entity  {
public:
	GalaxyMap(Composite* parent);
	virtual ~GalaxyMap();
	void loadMap();
	void saveMap();
	std::list<MapSector*> sectors;
};

#endif