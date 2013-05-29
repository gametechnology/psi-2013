#include "AsteroidSector.h"
#include "SectorManager.h"

using namespace irr;
using namespace irr::core;
using namespace irr::video;

AsteroidSector::AsteroidSector(Core* core, SectorManager* sectormanager, std::string skyBoxTexture, float boundryRadius, unsigned int amountWormHoles) : SectorTemplate(core, sectormanager, skyBoxTexture,boundryRadius,amountWormHoles) {
	init();
	_core = core;
}

void AsteroidSector::init(){
	if(Network::GetInstance()->IsServer())
	{
		for(int k = 2; k < 100; k++)
		{
			vector3df pos = vector3df((float)((rand() % 1500) - 750), (float)((rand() % 1500) - 750), (float)((rand() % 1500) - 750));
			vector3df vel = vector3df((float)((rand() % 15) - 7,5)/100, (float)((rand() % 15) - 7,5)/100, (float)((rand() % 15) - 7,5)/100);
			_enemyList.push_back(new EnemyAsteroid(_core->getSmgr(), pos,vel));
			
			addComponent(_enemyList.back());
		}
	}
}

void AsteroidSector::update(){
	SectorTemplate::update();
}


AsteroidSector::~AsteroidSector() {
	SectorTemplate::~SectorTemplate();
}


AstroidPlaceholder::AstroidPlaceholder(Core* core, Composite* parent) : GameObject()
{
	_core = core;
}

void AstroidPlaceholder::onAdd() 
{
	PrimitiveComponent* sphere;
	
	sphere = new PrimitiveComponent(_core->getSmgr(), PrimitiveComponent::PrimitiveType::PRIM_SPHERE, 2, 
		vector3df((float)((rand() % 1500) - 750), (float)((rand() % 1500) - 750), (float)((rand() % 1500) - 750)));

	addComponent(sphere);
	
	sphere->getNode()->setMaterialFlag(EMF_LIGHTING, false);
	sphere->getNode()->setMaterialFlag(EMF_FOG_ENABLE, true);

	_rotation = &vector3df((float)(rand() % 90), (float)(rand() % 90), (float)(rand() % 90));
	_velocity = &vector3df(100, 100, 100);
}

AstroidPlaceholder::~AstroidPlaceholder() 
{
}