/*
	Example entity for loading a model
*/

#ifndef SECTOR_MANAGER
#define SECTOR_MANAGER

#include "Engine/Entity.h"
class SectorManager : public Entity  {
public:
	SectorManager(Composite* parent);
	void SectorManager::handleMessage(unsigned int message, void* data = 0);
	virtual ~SectorManager();
};

#endif
