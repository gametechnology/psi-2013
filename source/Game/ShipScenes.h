#ifndef SHIP_SCENES
#define SHIP_SCENES

#include <Engine/Core.h>
#include <Engine/Interface.h>
#include <Engine/Scene.h>
#include <Engine/GameObject.h>
#include <Engine/CameraComponent.h>

#include "Player.h"
#include "Ship.h"
#include "EnemyManager.h"

class ShipScenes :	public Scene
{
public:
	ShipScenes(Core*, Interface*);
	~ShipScenes();
	
	virtual void init();
private:
	Core* _core;
	Interface* _interface;

	GameObject* ship;
	CameraComponent* camera;
};

#endif

