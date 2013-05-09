#include "CollisionTestScene.h"

CollisionTestScene::CollisionTestScene() : Scene() {

}

void CollisionTestScene::onAdd() 
{
}

void CollisionTestScene::init() {
	// Create model entity
	_player = new Player();
	addChild(_player);
	_player->handleMessage(DAMAGE, new int(789));	// Send a message to player and components.

	// Create camera entity
	_camera = new Camera();
	_camera->transform->velocity->Z -= (float)0.001;
	addChild(_camera);

	Scene::init();
}

void CollisionTestScene::update() {
	Scene::update();
}


CollisionTestScene::~CollisionTestScene() {

}
