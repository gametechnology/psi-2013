#pragma once
#ifndef SECTOR_HOMEBASE
#define SECTOR_HOMEBASE

//#include "Engine/Entity.h"
#include "SectorTemplate.h"
#include "Engine/Game.h"
#include "SectorManager.h"

class SectorHomeBase : public SectorTemplate  {
public:

	SectorHomeBase(SectorManager* sectormanager, const io::path & skyBoxTexture, float boundry, unsigned int amountWormHoles, int type);
	void SectorHomeBase::handleMessage(unsigned int message, void* data = 0);
	virtual ~SectorHomeBase();

	virtual void onAdd();
	virtual void update();
private: 
	int _type;
};

#endif
#ifndef BASE_PLACEHOLDER
#define BASE_PLACEHOLDER
class BasePlaceholder : public Entity{
	public:
	irr::scene::IMeshSceneNode *node;

	BasePlaceholder(int type);
	virtual ~BasePlaceholder();

	virtual void onAdd();
	private:
		int _type;
};
#endif
