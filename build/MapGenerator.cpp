#include "MapGenerator.h"

MapGenerator::MapGenerator(void)
{
	//this->map new GalaxyMap();
}

MapGenerator::~MapGenerator(void)
{
}

void MapGenerator::init(int sectorCount, int minWormholes, int maxWormholes)
{
	this->sectorCount = sectorCount;
	this->minWormholes = minWormholes;
	this->maxWormholes = maxWormholes;
}

GalaxyMap* MapGenerator::createNewMap()
{
	this->createSectors();
	this->createConnections();

	return NULL;
}

void MapGenerator::createSectors()
{
	for(int i = 0; i < this->sectorCount; i++)
	{
		//this->map.sectors.add(new Sector());
	}
}

void MapGenerator::createConnections()
{
	/*for each(Sector sector in this->map.sectors)
	{
		std::cout << std::srand(this->map.sectors.length);
	}*/
}
