#ifndef MAPSECTOR
#define MAPSECTOR
#include "Engine\Entity.h"


enum typeSector {EMPTY = 0, ASTEROID = 1, NEBULA = 2, SOLAR = 3, HOME_BLUE = 4, HOME_RED = 5, TOTALTYPES = 6};
class MapSector : public Entity
{
public:
	
	std::list<MapSector*>* connections;
	std::string name;
	typeSector type;
	bool explored;

	MapSector(Composite *parent,std::string name,typeSector type);
	~MapSector(void);

	virtual void draw();

private:
	irr::video::ITexture* _mapSectorTexture;
};

#endif