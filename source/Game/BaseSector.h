#ifndef SECTOR_BASE
#define SECTOR_BASE

#include "SectorTemplate.h"
#include "Engine/Game.h"

class BaseSector : public SectorTemplate  {
public:
	BaseSector(Composite* parent, const io::path & skyBoxTexture, float boundry, unsigned int amountWormHoles);
	void handleMessage(unsigned int message, void* data = 0);
	virtual void update();
	void init();
	virtual ~BaseSector();
};

#endif
