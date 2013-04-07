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
	void setBalanceChances(std::vector<float> chancesType);
	GalaxyMap* createNewMap(float width = 300, float height = 300, float radiusSector = 15);
	void createSectors();
	void createConnections();

private:
	std::vector<std::string> nameprefix;
	std::vector<std::string> nameaddon;
	std::vector<std::string> nametype;
	std::vector<float> typeChances;
	int sectorCount;
	int minWormholes;
	int maxWormholes;

	typeSector getRandomType();
	vector3df randomPosition();
	bool collisionLineBetweenSectors(MapSector* sector1, MapSector* sector2);
	std::string nameGenerator(typeSector type);
	int dijkstra();
};

#endif
