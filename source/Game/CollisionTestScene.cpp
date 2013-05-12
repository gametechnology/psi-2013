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
	removeenemytestinitiationcheck = true;
	//createTestEnemies();
	Scene::init();
}

void CollisionTestScene::update() {

	//for now, press only once, else you will have too many enemies!
	if(game->input->isKeyboardButtonPressed(KEY_KEY_1))
	{
		std::cout << "Test Laser-Enemy is activated";
		createLaserTestObjects();
	}
	if(game->input->isKeyboardButtonPressed(KEY_KEY_2))
	{
		std::cout << "Test Bullet-Enemy is activated";
		createBulletTestObjects();
	}
	if(game->input->isKeyboardButtonPressed(KEY_KEY_3))
	{
		std::cout << "Test Laser-Bullet is activated";
		createLaserToBullet();
	}
	if(game->input->isKeyboardButtonPressed(KEY_KEY_9))
	{
		std::cout << "Test Remove Enemy is activated \n";
		createRemoveEnemyTest();
	}
	Scene::update();
}

void CollisionTestScene::createLaserTestObjects(){
	//Create a row of EnemyDrones
	for(int i = 0; i < 5; i++)
	{
		_enemyList.push_back(new EnemyDrone(irr::core::vector3df(0,0,(irr::f32)(i + (i * i)))));
		
		addChild(_enemyList.back());
	}

	//Create a row of EnemyFighters
	for(int j = 0; j < 5; j++)
	{
		_enemyList.push_back(new EnemyFighter(irr::core::vector3df(20,0,(irr::f32)(j + (j * j)))));
		
		addChild(_enemyList.back());
	}

	//Create a row of Enemy Asteroids
	for(int k = 0; k < 5; k++)
	{
		_enemyList.push_back(new EnemyAsteroid(irr::core::vector3df(-20,0,(irr::f32)(k + (k * k))), irr::core::vector3df(0,0,0.01f)));
		
		addChild(_enemyList.back());
	}

}
void CollisionTestScene::createBulletTestObjects(){

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

void CollisionTestScene::createLaserToBullet(){

}
CollisionTestScene::~CollisionTestScene() {

}

void CollisionTestScene::createRemoveEnemyTest()
{
	if (removeenemytestinitiationcheck)
	{
		_enemyList.push_back(new EnemyAsteroid(irr::core::vector3df(0,9,0), irr::core::vector3df(0.02f,0,0)));
		addChild(_enemyList.back());
		removeenemytestinitiationcheck = false;
		std::cout << "Test Remove Enemy is initiated, press again to execute \n";
	}
	else
	{
		_enemyList[0]->setPosition(irr::core::vector3df(10000,10000,10000));
		_enemyList[0]->update();
		_enemyList[0]->destroy();
		_enemyList[0]->parent->removeChild(_enemyList[0],true);
		std::cout << "Test Remove Enemy is executed succesfully \n";
		removeenemytestinitiationcheck = true;
	}
}
