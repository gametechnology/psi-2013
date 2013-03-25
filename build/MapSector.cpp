#include "MapSector.h"


MapSector::MapSector(Composite *parent,std::string name,enum type):Entity(parent)
{
	
	this->connections = new std::list<MapSector*>();
	this->name = name;
	this->type = type;
	this->explored = false;
}


MapSector::~MapSector(void)
{
}
