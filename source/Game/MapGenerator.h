#ifndef MAPGENERATOR
#define MAPGENERATOR

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include "GalaxyMap.h"

using namespace std;

class MapGenerator {
public:
	MapGenerator(int sectorCount, int minWormholes, int maxWormholes);
	virtual ~MapGenerator();

	void init();
	void setBalanceChances(std::vector<float> chancesType);
	std::vector<MapSector*>* createNewMap(float width = 300, float height = 300, float sectorRadius = 15);
	void createSectors();
	void createConnections();
	std::vector<MapSector*>* createStaticMap(float width = 300, float height = 300, float sectorRadius = 15);

private:
	std::vector<std::string> nameprefix;
	std::vector<std::string> nameaddon;
	std::vector<std::string> nametype;
	std::vector<float> typeChances;
	std::vector<MapSector*>* sectors;

	int sectorCount;
	int minWormholes;
	int maxWormholes;

	float _width;
	float _height;
	float _sectorRadius;

	typeSector getRandomType();
	irr::core::vector3df randomPosition();
	bool collisionLineBetweenSectors(MapSector* sector1, MapSector* sector2);
	std::string nameGenerator(typeSector type);
	int dijkstra();
};

#endif
