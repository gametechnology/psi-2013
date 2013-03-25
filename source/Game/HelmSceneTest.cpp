#include "HelmSceneTest.h"
#include "HelmStation.h"
#include "Engine/Camera.h"
#include "Ship.h"
#include "ShipMover.h"
#include "Skybox.h"
#include "Engine\Camera.h"

HelmSceneTest::HelmSceneTest(void)
{
}


HelmSceneTest::~HelmSceneTest(void)
{
	Scene::~Scene();
}

void HelmSceneTest::init()
{
	Camera* camera = new Camera(this, vector3df(0,-5, 10), vector3df(0,0,0));
	addComponent(camera);
	Skybox* skyBox = new Skybox(this);
	addComponent(skyBox);

	Ship* ship = new Ship(this);

	//HelmStation* helmStation = new HelmStation(this);
	//addComponent(helmStation);
	addComponent(shipMover);

	Camera* camera = new Camera(this, vector3df(0,4,-4), vector3df(0,4,0));
	camera->angularVelocity.X += (irr::f32)0.001;
	addComponent(camera);
}