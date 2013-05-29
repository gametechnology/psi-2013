#ifndef MAPGENERATOR
#define MAPGENERATOR

#include <Engine/Core.h>
#include "MapSector.h"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class MapGenerator {
public:
	MapGenerator(Core*, int sectorCount, int minWormholes, int maxWormholes);
	virtual ~MapGenerator();

	void init();
	void setBalanceChances(std::vector<float> chancesType);
	
	void createSectors();
	void createConnections();

	std::list<MapSector*>* createNewMap(float width = 300, float height = 300, float sectorRadius = 15);
	std::list<MapSector*>* createStaticMap(float width = 300, float height = 300, float sectorRadius = 15);

private:
	Core* _core;

	std::vector<std::string> nameprefix;
	std::vector<std::string> nameaddon;
	std::vector<std::string> nametype;
	std::vector<float> typeChances;
	std::list<MapSector*> sectors;

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

	/*
	* Dijkstra, nice. Bob, it's just as ambiguous. Refactor this function.
	* What does it do? Why does it return an int? Document this.
	*/
	int dijkstra();
};

#endif
