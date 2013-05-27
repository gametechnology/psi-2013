#ifndef SECTOR_ASTEROID
#define SECTOR_ASTEROID

#include <Engine/Core.h>
#include <Engine/GameObject.h>
#include <Engine/Composite.h>

#include "SectorTemplate.h"
#include "SectorManager.h"

class AsteroidSector : public SectorTemplate  {
public:

	AsteroidSector(SectorManager* sectormanager, const io::path & skyBoxTexture, float boundry, unsigned int amountWormHoles);
	virtual ~AsteroidSector();
	
	virtual void init();
	virtual void update();
	virtual void handleMessage(unsigned int message, void* data = 0);
};
#endif

/*
* TODO Check if this can get its own class or can be intergrated into an
* existing class. This looks and, frankly IS, hacky.
*/
#ifndef ASTROID_PLACEHOLDER
#define ASTROID_PLACEHOLDER

class AstroidPlaceholder : public GameObject
{
	public:
	AstroidPlaceholder(Composite* parent);
	virtual ~AstroidPlaceholder();
	virtual void onAdd();
	irr::scene::IMeshSceneNode *node;
};

#endif
