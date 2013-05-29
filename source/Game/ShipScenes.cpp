#include "ShipScenes.h"

using namespace irr;
using namespace irr::core;

ShipScenes::ShipScenes(Core* core, Interface* ui) : Scene("ShipScenes")
{
	_core = core;
	_interface = ui;
}

ShipScenes::~ShipScenes() 
{ 
	Scene::~Scene(); 
}


void ShipScenes::init()
{
	EnemyManager* manager;
	manager = new EnemyManager(_core->getSmgr());

	addComponent(new Player());
	addComponent(new Ship(_core, _interface, vector3df(0,0,0), vector3df(0,0,0)));
	addComponent(manager);
}