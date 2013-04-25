#pragma once
#ifndef SECTOR_HOMEBASE
#define SECTOR_HOMEBASE

//#include "Engine/Entity.h"
#include "SectorTemplate.h"
#include "Engine/Game.h"
#include "SectorManager.h"

class SectorHomeBase : public SectorTemplate  {
public:

	SectorHomeBase(SectorManager* sectormanager, const io::path & skyBoxTexture, float boundry, unsigned int amountWormHoles);
	void SectorHomeBase::handleMessage(unsigned int message, void* data = 0);
	virtual ~SectorHomeBase();

	virtual void onAdd();
	virtual void update();
};

#endif
#ifndef BASE_PLACEHOLDER
#define BASE_PLACEHOLDER
class BasePlaceholder : public Entity{
	public:
	BasePlaceholder();
	virtual ~BasePlaceholder();

	virtual void onAdd();
};
#endif
