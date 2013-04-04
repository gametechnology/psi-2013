#include "MapGenerator.h"
#include "MapSector.h"
#include <math.h>

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
	typeSector j = (typeSector)(rand() % (TOTALTYPES - 2));
	MapSector* homeBlue = new MapSector(map, nameGenerator(j), HOME_BLUE,map->radiusSector);
	homeBlue->position.set(randomPosition());
	map->sectors.push_back(homeBlue);

	j = (typeSector)(rand() % (TOTALTYPES - 2));
	MapSector* homeRed = new MapSector(map, nameGenerator(j), HOME_RED,map->radiusSector);
	homeRed->position.set(randomPosition());
	map->sectors.push_back(homeRed);
	
	for(int i = 0; i < sectorCount - 2; i++)
	{
		j = (typeSector)(rand() % (TOTALTYPES - 2));
		MapSector* sector = new MapSector(map, nameGenerator(j), j, map->radiusSector);
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
	for(std::list<MapSector*>::iterator i = map->sectors.begin(); i != map->sectors.end(); ++i)
	{
		for(std::list<MapSector*>::iterator j = map->sectors.begin(); j != map->sectors.end(); ++j)
		{
			if ((*i) == (*j))
			{
				continue;
			}
			if (!collisionLineBetweenSectors((*i), (*j)))
			{
				int wormholeCount = minWormholes + (rand() % (maxWormholes - minWormholes));
				if ((*i)->connections.size() < maxWormholes - 1 && (*j)->connections.size() < maxWormholes - 1)
				{
					(*i)->connections.push_back((*j));
					(*j)->connections.push_back((*i));
				}
			}
		}
	}
	
	for(std::list<MapSector*>::iterator i = map->sectors.begin(); i != map->sectors.end(); ++i)
	{
		if ((*i)->connections.size() <= minWormholes)
		{
			for(std::list<MapSector*>::iterator j = map->sectors.begin(); j != map->sectors.end(); ++j)
			{
				if (!collisionLineBetweenSectors((*i), (*j)))
				{
					(*i)->connections.push_back((*j));
					(*j)->connections.push_back((*i));
					if ((*i)->connections.size() >= minWormholes)
					{
						break;
					}
				}
			}
		}
	}
}

bool MapGenerator::collisionLineBetweenSectors(MapSector* sector1, MapSector* sector2)
{
	float ax, ay, bx, by, cx, cy, cr;
	ax = sector1->position.X;
	ay = sector1->position.Y;
	bx = sector2->position.X;
	by = sector2->position.Y;
	cr = map->radiusSector;

	for(std::list<MapSector*>::iterator i = map->sectors.begin(); i != map->sectors.end(); ++i)
	{
		if ((*i) == sector1 || (*i) == sector2)
		{
			continue;
		}
		cx = (*i)->position.X;
		cy = (*i)->position.Y;

		double vx = bx - ax;
		double vy = by - ay;
		double xdiff = ax - cx;
		double ydiff = ay - cy;
		double a = pow(vx, 2) + pow(vy, 2);
		double b = 2 * ((vx * xdiff) + (vy * ydiff));
		double c = pow(xdiff, 2) + pow(ydiff, 2) - pow(cr, 2);
		double quad = pow(b, 2) - (4 * a * c);
		if (quad >= 0)
		{
			// An infinite collision is happening, but let's not stop here
			float quadsqrt = sqrt(quad);
			for (int i = -1; i <= 1; i += 2)
			{
				// Returns the two coordinates of the intersection points
				float t = (i * -b + quadsqrt) / (2 * a);
				float x = ax + (i * vx * t);
				float y = ay + (i * vy * t);
				// If one of them is in the boundaries of the segment, it collides
				if (x >= min(ax, bx) && x <= max(ax, bx) && y >= min(ay, by) && y <= max(ay, by))
				{
					return true;
				}
			}
		}
	}
	return false;
}

std::string MapGenerator::nameGenerator(typeSector type)
{
	float rnd = rand() % nameprefix.size();
	std::string name = nameprefix.at(rnd) + " ";
	nameprefix.erase(nameprefix.begin() + rnd);

	if (rand() % 100 < 25)
	{
		name += nameaddon.at(rand() % nameaddon.size()) + " ";
	}

	switch(type)
	{
		case EMPTY:
			name += this->nametype.at(0);
			break;
		case ASTEROID:
			name += this->nametype.at(1);
			break;
		case NEBULA:
			name += this->nametype.at(2);
			break;
		case SOLAR:
			name += this->nametype.at(3);
			break;
		case HOME_BLUE:
		case HOME_RED:
			name += this->nametype.at(4);
			break;
		default:
			name += this->nametype.at(0);
	}
	return name;
}