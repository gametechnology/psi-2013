#ifndef MAPGENERATOR
#define MAPGENERATOR

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

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
	std::vector<std::string> nameprefix;
	std::vector<std::string> nameaddon;
	std::vector<std::string> nametype;
	int sectorCount;
	int minWormholes;
	int maxWormholes;

	vector3df randomPosition();
};

#endif
