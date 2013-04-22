#ifndef SECTOR_ASTEROID
#define SECTOR_ASTEROID

//#include "Engine/Entity.h"
#include "SectorTemplate.h"
#include "Engine/Game.h"
#include "SectorManager.h"

class AsteroidSector : public SectorTemplate  {
public:

	AsteroidSector(SectorManager* sectormanager, const io::path & skyBoxTexture, float boundry, unsigned int amountWormHoles);
	void AsteroidSector::handleMessage(unsigned int message, void* data = 0);
	virtual void AsteroidSector::update();
	void AsteroidSector::init();
	void destroy();
	virtual ~AsteroidSector();
};
#endif
#ifndef ASTROID_PLACEHOLDER
#define ASTROID_PLACEHOLDER
class AstroidPlaceholder : public Entity{
	public:
	AstroidPlaceholder(Composite* parent);
	virtual ~AstroidPlaceholder();
};
#endif
