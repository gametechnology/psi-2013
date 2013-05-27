#ifndef SECTOR_BASE
#define SECTOR_BASE

#include <Engine/Core.h>

#include "SectorTemplate.h"
#include "SectorManager.h"

class BaseSector : public SectorTemplate  {
public:
	BaseSector(SectorManager* sectormanager, std::string skyBoxTexture, float boundry, unsigned int amountWormHoles);
	virtual ~BaseSector();

	void handleMessage(unsigned int message, void* data = 0);
	virtual void update();
	void init();
};

#endif
