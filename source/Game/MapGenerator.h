#ifndef MAPGENERATOR
#define MAPGENERATOR

#include <stdio.h>
#include <iostream>

class GalaxyMap;

using namespace std;

class MapGenerator
{
public:
	GalaxyMap* map;

	MapGenerator(void);
	~MapGenerator(void);

	void init(int sectorCount, int minWormholes, int maxWormholes);
	GalaxyMap* createNewMap();
	void createSectors();
	void createConnections();

private:
	int sectorCount;
	int minWormholes;
	int maxWormholes;
};

#endif
