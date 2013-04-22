#ifndef SECTOR_BASE
#define SECTOR_BASE

#include "SectorTemplate.h"
#include "Engine/Game.h"
#include "SectorManager.h"

class BaseSector : public SectorTemplate  {
public:
	BaseSector(SectorManager* sectormanager, const io::path & skyBoxTexture, float boundry, unsigned int amountWormHoles);
	void handleMessage(unsigned int message, void* data = 0);
	virtual void update();
	void init();
	void destroy();
	virtual ~BaseSector();
};

#endif
