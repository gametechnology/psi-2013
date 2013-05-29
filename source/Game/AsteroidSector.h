#ifndef SECTOR_ASTEROID
#define SECTOR_ASTEROID

#include <Engine/Core.h>
#include <Engine/GameObject.h>
#include <Engine/Composite.h>
#include <Engine/PrimitiveComponent.h>

#include "SectorTemplate.h"

#include "Messages.h"

class SectorManager;

class AsteroidSector : public SectorTemplate
{
public:
	AsteroidSector(Core*, SectorManager* sectormanager, std::string skyBoxTexture, float boundry, unsigned int amountWormHoles);
	virtual ~AsteroidSector();

	virtual void init();
	virtual void update();
	virtual void handleMessage(unsigned int message, void* data = 0) { };
private:
	Core* _core;
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
	AstroidPlaceholder(Core*, Composite* parent);
	virtual ~AstroidPlaceholder();
	virtual void onAdd();
	irr::scene::IMeshSceneNode *node;
private:
	Core* _core; 
};

#endif
