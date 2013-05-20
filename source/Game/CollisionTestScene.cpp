#include "CollisionTestScene.h"
	
//Make a dummy EnemyFighter to shoot at
EnemyFighter* dummyFighter = new EnemyFighter(irr::core::vector3df(10,10,10));

//Creates a dummy ship, without any extra properties
DummyShip* _ship = new DummyShip(vector3df(10,10,10));
Ship* playerShip = new Ship(vector3df(10,10,10), vector3df(0));
CollisionTestScene::CollisionTestScene(void) : Scene() 
{
	//Create a list of the enemies
	this->_enemyList = vector<Enemy*>();
	//Uses the Pool Design pattern to create lasers and add them to each EnemyFighter
	ObjectPool<Laser>* laserPool = new ObjectPool<Laser>(50);
	EnemyFighter::laserPool = *laserPool;
}

void CollisionTestScene::onAdd() 
{
}

void CollisionTestScene::init() {
	//add a first person camera to fly through the space
	this->game->device->getSceneManager()->addCameraSceneNodeFPS();
	
	removeenemytestinitiationcheck = true;
	//createTestEnemies();
	//dummyFighter->setVelocity(irr::core::vector3df(0.01f,0,0));
	//addChild(dummyFighter);
	addChild(_ship);
	Scene::init();
}

void CollisionTestScene::update() {

	//Using the Input Manager, different scenes are created
	if(game->input->isKeyboardButtonPressed(KEY_KEY_1))
	{
		std::cout << "Test Laser-Enemy is activated \n";
		createLaserTestObjects();
	}
	if(game->input->isKeyboardButtonPressed(KEY_KEY_2))
	{
		std::cout << "Test Bullet-Enemy is activated \n";
		createBulletTestObjects();
	}
	if(game->input->isKeyboardButtonPressed(KEY_KEY_3))
	{
		std::cout << "Test Laser-Bullet is activated \n";
		createLaserToBullet();
	}
	if(game->input->isKeyboardButtonPressed(KEY_KEY_4))
	{
		std::cout << "Test Laser-Ship is activated \n";
		createLaserAndShip();
	}
	if(game->input->isKeyboardButtonPressed(KEY_KEY_5))
	{
		std::cout << "Test Remove Enemy is activated \n";
		createRemoveEnemyTest();
	}

	//Tell the other EnemyFighters to shoot at target dummy	
	for(int l = 0; l < _enemyList.size(); l++)
	{
		if(_enemyList[l]->getType() == _enemyList[l]->FIGHTER)
		{
			//_enemyList[l]->inRangeList.push_back(dummyFighter);	
			if(_enemyList[0] != NULL&&_enemyList[1]!=NULL)
			{
				_enemyList[l]->inRangeList.push_back(_enemyList[0]); //to drone 1
				_enemyList[l]->inRangeList.push_back(_enemyList[1]);
			}
			
			//_enemyList[l]->inRangeList.push_back(_enemyList[7]); //to asteroid 1
			//_enemyList[l]->inRangeList.push_back(_enemyList[11]); //to asteroid 1
		}
	}

	Scene::update();
}

//Debug Key 1
void CollisionTestScene::createLaserTestObjects(){
	//Create a row of EnemyDrones
	for(int i = 0; i < 2; i++) //create only 1 in stead of 5 for testing.
	{
		_enemyList.push_back(new EnemyDrone(irr::core::vector3df(0,0,(irr::f32)(i + (i * i)))));
		
		addChild(_enemyList.back());
	}

	//Create a row of EnemyFighters
	for(int j = 0; j < 1; j++)
	{
		_enemyList.push_back(new EnemyFighter(irr::core::vector3df(20,0,(irr::f32)(j + (j * j)))));
		addChild(_enemyList.back());
	}

	//Create a row of Enemy Asteroids
	for(int k = 0; k < 1; k++)
	{
		_enemyList.push_back(new EnemyAsteroid(irr::core::vector3df(-20,0,(irr::f32)(k + (k * k))), irr::core::vector3df(0,0,0.01f)));
		
		addChild(_enemyList.back());
	}

}
//Debug Key 2
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
//Debug Key 3
void CollisionTestScene::createLaserToBullet(){

}
//Debug Key 4
void CollisionTestScene::createLaserAndShip(){
	
	//Create a row of EnemyFighters
	for(int j = 0; j < 5; j++)
	{
		_enemyList.push_back(new EnemyFighter(irr::core::vector3df(20,0,(irr::f32)(j + (j * j)))));
		addChild(_enemyList.back());
	}
}

CollisionTestScene::~CollisionTestScene() {

}
//Debug Key 5
void CollisionTestScene::createRemoveEnemyTest()
{
	if (removeenemytestinitiationcheck)
	{
		_enemyList.push_back(new EnemyAsteroid(irr::core::vector3df(0,0,0), irr::core::vector3df(0.02f,0,0)));
		addChild(_enemyList.back());
		removeenemytestinitiationcheck = false;
		std::cout << "Test Remove Enemy is initiated, press again to execute \n";
	}
	else
	{
		for (unsigned int i = 0; i < _enemyList.size(); i++)
		{
			_enemyList[i]->destroy();
		//	delete _enemyList[i];
		}
		_enemyList.clear();
		
		std::cout << "Test Remove Enemy is executed succesfully \n";
		removeenemytestinitiationcheck = true;
	}
}
