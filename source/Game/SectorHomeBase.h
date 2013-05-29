#ifndef SECTOR_HOMEBASE
#define SECTOR_HOMEBASE

#include <Engine/Core.h>
#include <Engine/PrimitiveComponent.h>

#include "SectorTemplate.h"

#include "Messages.h"

class SectorHomeBase : public SectorTemplate
{
public:
	SectorHomeBase(Core*, SectorManager* sectormanager, std::string skyBoxTexture, float boundry, unsigned int amountWormHoles);
	virtual ~SectorHomeBase();

	virtual void handleMessage(unsigned int message, void* data = 0) { };
	virtual void init();
	virtual void update();
private:
	Core* _core;
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
	BasePlaceholder(Core*);
	virtual ~BasePlaceholder();

	virtual void init();
private:
	Core* _core;
	irr::scene::IMeshSceneNode *node;
};

#endif
