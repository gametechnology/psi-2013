#include "CollisionTestScene.h"

CollisionTestScene::CollisionTestScene(void) : Scene() 
{
	//Create a list of the enemies
	this->_enemyList = vector<Enemy*>();
}

void CollisionTestScene::onAdd() 
{
}

void CollisionTestScene::init() {
	//add a first person camera to fly through the space
	this->game->device->getSceneManager()->addCameraSceneNodeFPS();
	createTestEnemies();
	Scene::init();
}

void CollisionTestScene::update() {
	Scene::update();
}

void CollisionTestScene::createTestEnemies(){

	//Create a row of EnemyDrones
	for(int i = 0; i < 5; i++)
	{
		_enemyList.push_back(new EnemyDrone(irr::core::vector3df(0,0,(irr::f32)(i + (i * i)))));
		
		addChild(_enemyList.back());
	}

	//Create a row of EnemyFighters
	for(int j = 2; j < 5; j++)
	{
		_enemyList.push_back(new EnemyFighter(irr::core::vector3df(0,(irr::f32)(j + (j * j)),0)));
		
		addChild(_enemyList.back());
	}

	//Create a row of Enemy Asteroids
	for(int k = 2; k < 5; k++)
	{
		_enemyList.push_back(new EnemyAsteroid(irr::core::vector3df((irr::f32)(k + (k * k)),0,0), irr::core::vector3df(0,0,0.01f)));
		
		addChild(_enemyList.back());
	}

	_enemyList.push_back(new EnemyAsteroid(irr::core::vector3df(-10,0,0), irr::core::vector3df(0.02f,0,0)));
	addChild(_enemyList.back());
}


CollisionTestScene::~CollisionTestScene() {

}
