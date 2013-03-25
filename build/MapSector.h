#pragma once
#include "Engine\Entity.h"

class MapSector : public Entity
{
public:
	
	std::list<MapSector*>* connections;
	std::string name;
	enum typeSector {EMPTY, ASTEROID, NEBULA, HOME, SOLAR} type;
	bool explored;

	MapSector(Composite *parent,std::string name,enum type);
	~MapSector(void);


};

