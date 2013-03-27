#ifndef MAPSECTOR
#define MAPSECTOR
#include "Engine\Entity.h"


enum typeSector {EMPTY = 0, ASTEROID = 1, NEBULA = 2, HOME = 3, SOLAR = 4, TOTALTYPES = 5};
class MapSector : public Entity
{
public:
	
	std::list<MapSector*>* connections;
	std::string name;
	typeSector type;
	bool explored;

	MapSector(Composite *parent,std::string name,enum typeSector);
	~MapSector(void);


};

#endif