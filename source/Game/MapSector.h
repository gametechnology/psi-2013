#ifndef MAPSECTOR
#define MAPSECTOR

#include <Engine\GameObject.h>
#include <string>
#include <vector>

enum typeSector
{
	EMPTY = 0,
	ASTEROID, 
	NEBULA, 
	SOLAR, 
	HOME_BLUE, 
	HOME_RED, 
	TOTALTYPES
};

class MapSector : public GameObject
{
public:	
	std::vector<MapSector*> connections;
	std::string name;
	typeSector type;
	bool explored;
	float radius;
	int distToBlueBase;

	MapSector(std::string name, typeSector type, float radius);
	~MapSector(void);

	virtual void onAdd();
	virtual void draw();
	void resetTexture();

private:
	irr::video::ITexture* _mapSectorTexture;
};

#endif