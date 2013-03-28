#include "WeaponScene.h"
#include "WeaponStation.h"
#include "Engine/Camera.h"
#include "Ship.h"
#include "ShipMover.h"
#include "Skybox.h"
#include "Engine\Camera.h"

WeaponScene::WeaponScene(void)
{
}


WeaponScene::~WeaponScene(void)
{
	Scene::~Scene();
}

void WeaponScene::init()
{
	Skybox* skyBox = new Skybox(this);
	addComponent(skyBox);

	//Ship* ship = new Ship(this);

	WeaponStation* weaponStation = new WeaponStation(this);
	addComponent(weaponStation);
	//addComponent(shipMover);

	Camera* camera = new Camera(this, vector3df(0,4,-4), vector3df(0,4,0));
	addComponent(camera);

	network = Net(true, camera);
}