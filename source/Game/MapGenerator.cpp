#include "MapGenerator.h"
#include "MapSector.h"

MapGenerator::MapGenerator(void)
{
	nameprefix.push_back("Dagobah");
	nameprefix.push_back("Bespin");
	nameprefix.push_back("Yavin 4");
	nameprefix.push_back("Kashyyyk");
	nameprefix.push_back("Pandora");
	nameprefix.push_back("Prometheus");
	nameprefix.push_back("Valhalla");
	nameprefix.push_back("Hyperion");
	nameprefix.push_back("Thea");
	nameprefix.push_back("Helio");
	nameprefix.push_back("Narvi");
	nameprefix.push_back("Thrymr");
	nameprefix.push_back("Cordelia");
	nameprefix.push_back("Ixion");
	nameprefix.push_back("X5");
	nameprefix.push_back("X6");
	nameprefix.push_back("X8");
	nameprefix.push_back("085");
	nameprefix.push_back("Echelon");
	nameprefix.push_back("Axowholla");
	nameprefix.push_back("Tatis");
	nameprefix.push_back("Undefined");
	nameprefix.push_back("urmottastinx");
	nameprefix.push_back("Unicorn");
	
	nameaddon.push_back("Alpha");
	nameaddon.push_back("Beta");
	nameaddon.push_back("Gamma");
	nameaddon.push_back("Delta");
	nameaddon.push_back("Teta");
	nameaddon.push_back("Omega");

	nametype.push_back("Sector");	//Empty
	nametype.push_back("Field");	//Asteroids		?belt?
	nametype.push_back("Nebula");	//Nebula
	nametype.push_back("System");	//Solar
	nametype.push_back("");	//Home
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

GalaxyMap* MapGenerator::createNewMap(float width, float height, float radiusSector)
{
	map = new GalaxyMap(NULL);
	map->widthMap = width;
	map->heightMap = height;
	map->radiusSector = radiusSector;

	this->createSectors();
	this->createConnections();

	return map;
}

void MapGenerator::createSectors()
{
	
	MapSector* homeBlue = new MapSector(map, "Blue Base", HOME_BLUE);
	homeBlue->position.set(randomPosition());
	map->sectors.push_back(homeBlue);

	MapSector* homeRed = new MapSector(map, "Red Base", HOME_RED);
	homeRed->position.set(randomPosition());
	map->sectors.push_back(homeRed);
	
	for(int i = 0; i < sectorCount - 2; i++)
	{
		MapSector* sector = new MapSector(map, "Sector " + i, (typeSector)(rand() % (TOTALTYPES - 2)));
		sector->position.set(randomPosition());
		map->sectors.push_back(sector);
	}
}

vector3df MapGenerator::randomPosition()
{
	vector3df randPos(map->radiusSector + rand() % ((int)(map->widthMap - (map->radiusSector * 2))), map->radiusSector + rand() % ((int)(map->heightMap - (map->radiusSector * 2))), 0);

	for(std::list<MapSector*>::iterator i = map->sectors.begin(); i != map->sectors.end(); ++i)
	{
		if ((*i)->position.getDistanceFrom(randPos) < map->radiusSector * 2)
		{
			randPos = randomPosition();
		}
	}
	return randPos;
}

void MapGenerator::createConnections()
{
	/*for each(Sector sector in this->map.sectors)
	{
		std::cout << std::srand(this->map.sectors.length);
	}*/
}
