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
	nametype.push_back("Sector");	//Home
}

MapGenerator::~MapGenerator(void)
{

}

void MapGenerator::init(int sectorCount, int minWormholes, int maxWormholes)
{
	this->sectorCount = sectorCount;
	this->minWormholes = minWormholes;
	this->maxWormholes = maxWormholes;
	for(int i = 0; i < TOTALTYPES - 2; i++)
	{
		this->typeChances.push_back(100/(TOTALTYPES - 2));
	}
}

void MapGenerator::setBalanceChances(std::vector<float> chancesType)
{
	this->typeChances = chancesType;
}

GalaxyMap* MapGenerator::createNewMap(float width, float height, float radiusSector)
{
	map = new GalaxyMap(NULL);
	map->widthMap = width;
	map->heightMap = height;
	map->radiusSector = radiusSector;
	float i = 0;
	for(std::vector<float>::iterator l = typeChances.begin(); l != typeChances.end(); ++l)
	{
		i += (*l);
	}
	if(i < 99) return NULL;
	this->createSectors();
	this->createConnections();

	return map;
}

void MapGenerator::createSectors()
{
	MapSector* homeBlue = new MapSector(map, nameGenerator(HOME_BLUE), HOME_BLUE,map->radiusSector);
	homeBlue->transform->position->set(randomPosition());
	map->sectors.push_back(homeBlue);

	MapSector* homeRed = new MapSector(map, nameGenerator(HOME_RED), HOME_RED,map->radiusSector);
	homeRed->transform->position->set(randomPosition());
	map->sectors.push_back(homeRed);
	
	typeSector j;
	for(int i = 0; i < sectorCount - 2; i++)
	{
		j = getRandomType();
		MapSector* sector = new MapSector(map, nameGenerator(j), j, map->radiusSector);
		sector->transform->position->set(randomPosition());
		map->sectors.push_back(sector);
	}
}

typeSector MapGenerator::getRandomType()
{//(typeSector)(rand() % (TOTALTYPES - 2));
	int i = rand() % 100;
	for(int j = 0; j < TOTALTYPES - 2; j++)
	{
		i -= (int)typeChances[j];
		if (i <= 0) return (typeSector)(j);
	}
	return EMPTY;
}

irr::core::vector3df MapGenerator::randomPosition()
{
	irr::core::vector3df randPos(map->radiusSector + rand() % ((int)(map->widthMap - (map->radiusSector * 2))), map->radiusSector + rand() % ((int)(map->heightMap - (map->radiusSector * 2))), 0);

	for(std::list<MapSector*>::iterator i = map->sectors.begin(); i != map->sectors.end(); ++i)
	{
		if ((*i)->transform->position->getDistanceFrom(randPos) < map->radiusSector * 2)
		{
			randPos = randomPosition();
		}
	}
	return randPos;
}

void MapGenerator::createConnections()
{
	for (std::list<MapSector*>::iterator h = map->sectors.begin(); h != map->sectors.end(); ++h)
	{
		(*h)->connections.clear();
	}
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
				if ((int)((*i)->connections.size()) < maxWormholes - 1 && (int)((*j)->connections.size()) < maxWormholes - 1)
				{
					(*i)->connections.push_back((*j));
					(*j)->connections.push_back((*i));
				}
			}
		}
	}
	
	for(std::list<MapSector*>::iterator i = map->sectors.begin(); i != map->sectors.end(); ++i)
	{
		if ((int)((*i)->connections.size()) <= minWormholes)
		{
			for(std::list<MapSector*>::iterator j = map->sectors.begin(); j != map->sectors.end(); ++j)
			{
				if (!collisionLineBetweenSectors((*i), (*j)))
				{
					(*i)->connections.push_back((*j));
					(*j)->connections.push_back((*i));
					if ((int)((*i)->connections.size()) >= minWormholes)
					{
						break;
					}
				}
			}
		}
	}
	//Fill in the distance to blue base for every sector
	dijkstra();
	
	//Place the red base as far as possible from the blue base
	MapSector* away = map->sectors.back();
	MapSector* red;
	std::string tempName;
	typeSector tempType;
	//Find the red base and the base furthest from blue base
	for(std::list<MapSector*>::iterator i = map->sectors.begin(); i != map->sectors.end(); ++i)
	{
		if ((*i)->type == HOME_RED)
		{
			red = (*i);
		} else if ((*i)->distToBlueBase > away->distToBlueBase && (*i)->distToBlueBase != INT_MAX && (*i)->type != HOME_RED)
		{
			away = (*i);
		}
		//check if distToBlueBase != INT_MAX, else make another connection to one with low distToBlueBase;
	}
	//Swap HOME_RED with furthest MapSector and reset the textures;
	tempName = away->name;
	tempType = away->type;
	away->name = red->name;
	away->type = red->type;
	red->name = tempName;
	red->type = tempType;
	away->resetTexture();
	red->resetTexture();

	//Redo the distance to blue base calculation
	int j = dijkstra();
}

bool MapGenerator::collisionLineBetweenSectors(MapSector* sector1, MapSector* sector2)
{
	float ax, ay, bx, by, cx, cy, cr;
	ax = sector1->transform->position->X;
	ay = sector1->transform->position->Y;
	bx = sector2->transform->position->X;
	by = sector2->transform->position->Y;
	cr = map->radiusSector;

	for(std::list<MapSector*>::iterator i = map->sectors.begin(); i != map->sectors.end(); ++i)
	{
		if ((*i) == sector1 || (*i) == sector2)
		{
			continue;
		}
		cx = (*i)->transform->position->X;
		cy = (*i)->transform->position->Y;

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
			double quadsqrt = sqrt(quad);
			for (int i = -1; i <= 1; i += 2)
			{
				// Returns the two coordinates of the intersection points
				double t = (i * -b + quadsqrt) / (2 * a);
				double x = ax + (i * vx * t);
				double y = ay + (i * vy * t);
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
	//Pick a random name and remove it from the list to avoid duplicates
	int rnd = rand() % nameprefix.size();
	std::string name = nameprefix.at(rnd) + " ";
	nameprefix.erase(nameprefix.begin() + rnd);

	//In some cases add a middle name
	if (rand() % 100 < 25)
	{
		name += nameaddon.at(rand() % nameaddon.size()) + " ";
	}

	//End the name with the name for the type of the sector
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

int MapGenerator::dijkstra()
{
	for (std::list<MapSector*>::iterator i = map->sectors.begin(); i != map->sectors.end(); ++i)
	{
		(*i)->distToBlueBase = INT_MAX;
	}

	std::list<MapSector*> openConnections;
	std::list<MapSector*> nextConnections;
	std::list<MapSector*> shortestPath;
	int curDist = 0;
	openConnections.push_back(map->sectors.front());

	while(openConnections.size() > 0)
	{
		nextConnections.clear();
		for (std::list<MapSector*>::iterator i = openConnections.begin(); i != openConnections.end(); ++i)
		{
			if ((*i)->distToBlueBase > curDist)
			{
				(*i)->distToBlueBase = curDist;
				for (std::list<MapSector*>::iterator j = (*i)->connections.begin(); j != (*i)->connections.end(); ++j)
				{
					nextConnections.push_back((*j));
				}
			}
		}
		openConnections = nextConnections;

		curDist++;
	}
	for (std::list<MapSector*>::iterator i = map->sectors.begin(); i != map->sectors.end(); ++i)
	{
		if ((*i)->type == HOME_RED)
		{
			return (*i)->distToBlueBase;
		}
	}
	return 0;
}