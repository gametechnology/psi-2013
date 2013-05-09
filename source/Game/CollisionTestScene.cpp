#include "CollisionTestScene.h"

CollisionTestScene::CollisionTestScene(void) : Scene() 
{
	//Network::GetInstance()->AddListener(SERVER_ENEMY, this);
	this->_enemyList = vector<Enemy*>();
	_player1 = new EnemyPlayer(irr::core::vector3df(0,1,0),irr::core::vector3df(0,0,0));
	addChild(_player1);
	_player2 = new EnemyPlayer(irr::core::vector3df(20,1,0),irr::core::vector3df(-1,0,0));
	addChild(_player2);
}

void CollisionTestScene::onAdd() 
{
}

void CollisionTestScene::init() {
	// Create model entity
	/*_player = new Player();
	addChild(_player);
	_player->handleMessage(DAMAGE, new int(789));	// Send a message to player and components.

	// Create camera entity
	_camera = new Camera();
	_camera->transform->velocity->Z -= (float)0.001;
	addChild(_camera);*/

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
