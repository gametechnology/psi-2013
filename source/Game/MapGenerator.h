#ifndef MAPGENERATOR
#define MAPGENERATOR

#include <stdio.h>
#include <iostream>

#include "GalaxyMap.h"

using namespace std;

class MapGenerator
{
public:
	GalaxyMap* map;

	MapGenerator(void);
	~MapGenerator(void);

	void init(int sectorCount, int minWormholes, int maxWormholes);
	GalaxyMap* createNewMap(float width = 300, float height = 300, float radiusSector = 10);
	void createSectors();
	void createConnections();

private:
	int sectorCount;
	int minWormholes;
	int maxWormholes;

	vector3df randomPosition();
};

#endif
