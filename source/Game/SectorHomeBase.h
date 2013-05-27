#ifndef SECTOR_HOMEBASE
#define SECTOR_HOMEBASE

#include <Engine/Core.h>

#include "SectorTemplate.h"
#include "SectorManager.h"

class SectorHomeBase : public SectorTemplate
{
public:
	SectorHomeBase(SectorManager* sectormanager, const io::path & skyBoxTexture, float boundry, unsigned int amountWormHoles);
	virtual ~SectorHomeBase();

	virtual void handleMessage(unsigned int message, void* data = 0);
	virtual void onAdd();
	virtual void update();
};

#endif

/*
* TODO Check if this can get its own class or can be intergrated into an
* existing class. This looks and, frankly IS, hacky.
*/
#ifndef BASE_PLACEHOLDER
#define BASE_PLACEHOLDER

class BasePlaceholder : public GameObject
{
public:
	BasePlaceholder();
	virtual ~BasePlaceholder();
private:
	irr::scene::IMeshSceneNode *node;
};

#endif
