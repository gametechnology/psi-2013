#ifndef MAPSECTOR
#define MAPSECTOR
#include "Engine\Entity.h"


enum typeSector {EMPTY = 0, ASTEROID = 1, NEBULA = 2, SOLAR = 3, HOME_BLUE = 4, HOME_RED = 5, TOTALTYPES = 6};
class MapSector : public Entity
{
public:
	
	std::list<MapSector*> connections;
	std::string name;
	typeSector type;
	bool explored;
	float radius;
	int distToBlueBase;

	MapSector(Composite *parent,std::string name,typeSector type, float radius);
	~MapSector(void);

	virtual void draw();
	void resetTexture();

private:
	irr::video::ITexture* _mapSectorTexture;
};

#endif