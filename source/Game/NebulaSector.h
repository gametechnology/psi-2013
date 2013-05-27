#ifndef SECTOR_NEBULA
#define SECTOR_NEBULA

#include "SectorTemplate.h"
#include <Engine/Core.h>

class NebulaSector : public SectorTemplate
{
public:
	NebulaSector(SectorManager* parent, std::string skyBoxTexture, float boundry, unsigned int amountWormHoles);
	virtual ~NebulaSector();

	virtual void update();
	virtual void init();	
	virtual void handleMessage(unsigned int message, void* data = 0);
};

#endif
