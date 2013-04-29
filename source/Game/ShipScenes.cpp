#include "ShipScenes.h"
#include "Player.h"
#include "Ship.h"
#include "EnemyManager.h"

ShipScenes::ShipScenes(void) {}
ShipScenes::~ShipScenes(void) { Scene::~Scene(); }


void ShipScenes::init()
{
	
	EnemyManager* manager;
	manager = new EnemyManager();

	addChild(new Player());
	addChild(new Ship(irr::core::vector3df(0,0,0), irr::core::vector3df(0,0,0)));
	addComponent(manager);
}