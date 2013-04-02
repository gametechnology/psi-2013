/*
	Example entity for loading a model
*/

#ifndef SECTOR_MANAGER
#define SECTOR_MANAGER

#include "Engine/Scene.h"
#include "SectorTemplate.h"
class SectorManager : public Scene  {
public:
	SectorManager();
	void SectorManager::handleMessage(unsigned int message, void* data = 0);
	void SectorManager::init();
	virtual ~SectorManager();
private:
	SectorTemplate *_currentSector;
};

#endif
