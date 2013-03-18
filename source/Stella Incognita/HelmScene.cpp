#include "HelmScene.h"
#include "irrlicht.h"
#include "Game.h"
#include "Composite.h"
#include "Component.h"
#include "Camera.h"
#include <list>
#include "Messages.h"
#include "KeyEventReceiver.h"

IrrlichtDevice* HelmScene::device;

HelmScene::HelmScene(void) {

}

void HelmScene::init() {
	u32 then = device->getTimer()->getTime();
	device->setEventReceiver(rv);
	//HelmScene::
	// Create camera entity
	//Camera* camera = new Camera(this, vector3df(0,4,-4), vector3df(0,4,0));
	//camera->velocity.Z -= 0.001;
	//addComponent(camera);
}

void HelmScene::createRandomPlanets( int amountOfPlanets ){
	float randX = 0;
	float randY = 0;
	float randZ = 0;
	for(int i=0; i < amountOfPlanets; i++){
		randX = rand() % 10000 - 5000; // -5000 - 5000
		randY = rand() % 10000 - 5000; // -5000 - 5000
		randZ = rand() % 10000 - 5000; // -5000 - 5000
		planet = new BasicObject(vector3df(randX,randY,randZ), "../Assets/asteroid3DS.3DS", "");
	}
}

void HelmScene::update() {
	// Work out a frame delta time.
	const u32 now = device->getTimer()->getTime();
	const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
	then = now;
}

HelmScene::~HelmScene(void) {
	Scene::~Scene();
}
