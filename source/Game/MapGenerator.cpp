#include "MapGenerator.h"
#include "MapSector.h"

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
	map = new GalaxyMap(NULL);
	this->createSectors();
	this->createConnections();

	return map;
}

void MapGenerator::createSectors()
{
	float widthMap = 300;
	float heightMap = 300;
	float radiusSector = 10;
	for(int i = 0; i < sectorCount; i++)
	{
		MapSector* sector = new MapSector(map, "Sector " + i, (typeSector)(rand() % TOTALTYPES));
		map->sectors.push_back(sector);
		sector->position.set(vector3df(radiusSector + rand() % ((int)(widthMap - radiusSector)), radiusSector + rand() % ((int)(heightMap - radiusSector)), 0));
	}
	// some bad code to check collision
	for (std::list<MapSector*>::iterator i = map->sectors.begin(); i != map->sectors.end(); ++i)
	{
		for (std::list<MapSector*>::iterator j = i; j != map->sectors.end(); ++j)
		{
			if (i == j) continue;
			if ((*i)->position.getDistanceFrom((*j)->position) < (radiusSector * 2))
			{
				bool goodNow = true;
				while(goodNow)
				{
					goodNow = true;
					(*j)->position.set(vector3df(radiusSector + rand() % ((int)(widthMap - radiusSector)), radiusSector + rand() % ((int)(heightMap - radiusSector)), 0));
					for (std::list<MapSector*>::iterator k = map->sectors.begin(); k != map->sectors.end(); ++k)
					{
						if (k == j) continue;
						if ((*j)->position.getDistanceFrom((*k)->position) < (radiusSector * 2))
						{
							goodNow = false;
							break;
						}
					}
				}
			}
		}
	}
}

void MapGenerator::createConnections()
{
	/*for each(Sector sector in this->map.sectors)
	{
		std::cout << std::srand(this->map.sectors.length);
	}*/
}
