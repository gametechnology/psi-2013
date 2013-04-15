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

	addComponent(new Player(this));
	addComponent(new Ship(this));
	addComponent(manager);
}