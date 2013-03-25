#include "HelmSceneTest.h"
#include "HelmStation.h"
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
	Skybox* skyBox = new Skybox(this);
	addComponent(skyBox);

	HelmStation* helmStation = new HelmStation(this);
	addComponent(helmStation);

	ShipMover* shipMover = new ShipMover(this);
	addComponent(shipMover);

	Camera* camera = new Camera(this, vector3df(0,4,-4), vector3df(0,4,0));
	camera->angularVelocity.X += (irr::f32)0.001;
	addComponent(camera);
}