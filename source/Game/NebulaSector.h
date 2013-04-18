#ifndef SECTOR_NEBULA
#define SECTOR_NEBULA

#include "SectorTemplate.h"
#include "Engine/Game.h"

class NebulaSector : public SectorTemplate  {
public:

	NebulaSector(SectorManager* parent, const io::path& skyBoxTexture, float boundry, unsigned int amountWormHoles);
	void NebulaSector::handleMessage(unsigned int message, void* data = 0);
	virtual void NebulaSector::update();
	void NebulaSector::init();
	virtual ~NebulaSector();
};

#endif
