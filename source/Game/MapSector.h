#ifndef MAPSECTOR
#define MAPSECTOR
#include "Engine\Entity.h"
#include "NetworkInterface.h"
#include <string>
#include <vector>

enum typeSector {EMPTY = 0, ASTEROID = 1, NEBULA = 2, SOLAR = 3, HOME_BLUE = 4, HOME_RED = 5, TOTALTYPES = 6};
class MapSector : public Entity {
public:
	
	std::vector<MapSector*> connections;
	std::string name;
	typeSector type;
	bool explored;
	float radius;
	int distToBlueBase;
	irr::io::path skyboxTexture;
	int connectionSize;

	static int uid;
	int _id;

	MapSector(std::string name,typeSector type, float radius);
	~MapSector(void);
	
	int getId();

	virtual void onAdd();
	virtual void draw();
	void resetTexture();

	void SetSkyboxTexture(const irr::io::path & texture);
	
private:
	irr::video::ITexture* _mapSectorTexture;
};

#endif