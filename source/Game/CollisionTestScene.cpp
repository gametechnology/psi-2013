#include "CollisionTestScene.h"
	
//Make a dummy EnemyFighter to shoot at
EnemyFighter* dummyFighter = new EnemyFighter(irr::core::vector3df(10,10,10));

//Creates a dummy ship, without any extra properties
Ship* playerShip = new Ship(vector3df(10,10,10), vector3df(0));

int target=0; 

CollisionTestScene::CollisionTestScene(void) : Scene() 
{
	//Create a list of the enemies
	this->_enemyList = vector<Enemy*>();
	//Uses the Pool Design pattern to create lasers and add them to each EnemyFighter
	ObjectPool<Laser>* laserPool = new ObjectPool<Laser>(500);
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
	//addChild(_ship);
	Scene::init();
}

void CollisionTestScene::update() {

	//Using the Input Manager, different targets are set
	//key 2=drone, key3=fighter, key4=asteroid, key5=ship
	if(game->input->isKeyboardButtonPressed(KEY_KEY_1))
	{
		std::cout << "Test Laser-Enemy is activated \n";
		createLaserTestObjects();
	}
	if(game->input->isKeyboardButtonPressed(KEY_KEY_2))
	{
		std::cout << "Target is drone";
		target = 1;
	}
	if(game->input->isKeyboardButtonPressed(KEY_KEY_3))
	{
		std::cout << "Target is Fighter";
		target = 2;
	}
	if(game->input->isKeyboardButtonPressed(KEY_KEY_4))
	{
		std::cout << "Target is asteroid";
		target = 3;
	}
	if(game->input->isKeyboardButtonPressed(KEY_KEY_5))
	{
		std::cout << "Target is dummyship";
		target = 4;
	}
	if(game->input->isKeyboardButtonPressed(KEY_KEY_8))
	{
		std::cout << "Test Remove Enemy is activated \n";
		createRemoveEnemyTest();
	}
	if(game->input->isKeyboardButtonPressed(KEY_KEY_9))
	{
		std::cout << "Remove All enemies \n";
		RemoveAllEnemies();
	}

	//std::cout<<"target " << target;
	//Tell the other EnemyFighters to shoot at target 	
	for(int l = 0; l < _enemyList.size(); l++)
	{
		if(_enemyList[l]->getType() == _enemyList[l]->FIGHTER)
		{
			if(_enemyList.size() >= 2)
			{
				switch(target)
				{
					case 1:
					{	
						if(_enemyList.size()>=2)
						{
							if(_enemyList[0] != NULL&&_enemyList[1]!=NULL)
							{
								_enemyList[l]->inRangeList.push_back(_enemyList[0]); //to drone 1
								_enemyList[l]->inRangeList.push_back(_enemyList[1]);
							}
						}
					}break;
					case 2:
					{
						if(_enemyList.size()>=4)
						{
							if(_enemyList[0] != NULL&&_enemyList[1]!=NULL&&_enemyList[2] != NULL&&_enemyList[3]!=NULL)
							{
								_enemyList[l]->inRangeList.push_back(_enemyList[2]); //to fighter 1
								_enemyList[l]->inRangeList.push_back(_enemyList[3]);
							}
						}
					}break;
					case 3:
					{
						if(_enemyList.size()>=6)
						{
							if(_enemyList[0] != NULL&&_enemyList[1]!=NULL&&_enemyList[2] != NULL&&_enemyList[3]!=NULL&&_enemyList[4] != NULL&&_enemyList[5]!=NULL)
							{
								_enemyList[l]->inRangeList.push_back(_enemyList[4]); //to asteroid 1
								_enemyList[l]->inRangeList.push_back(_enemyList[5]);
							}
						}
					}break;
					case 4:
					{
						if(_enemyList.size()>=7)
						{
							if(_enemyList[0] != NULL&&_enemyList[1]!=NULL&&_enemyList[2] != NULL&&_enemyList[3]!=NULL&&_enemyList[4] != NULL&&_enemyList[5]!=NULL&&_enemyList[6] != NULL)
							{
								_enemyList[l]->inRangeList.push_back(_enemyList[6]); //to dummyship
							}
						}
					}break;
				}				
			}			
		}
	}

	Scene::update();
}

//Debug Key 1
void CollisionTestScene::createLaserTestObjects(){
	//Create a row of EnemyDrones
	for(int i = 0; i < 2; i++) //create only 2 in stead of 5 for testing.
	{
		_enemyList.push_back(new EnemyDrone(irr::core::vector3df(0,(irr::f32)(i + (i * i)+10*i),(irr::f32)(i + (i * i)+10*i))));
		
		addChild(_enemyList.back());
	}

	//Create a row of EnemyFighters
	for(int j = 0; j < 2; j++)
	{
		_enemyList.push_back(new EnemyFighter(irr::core::vector3df(20,(irr::f32)(j + (j * j)+10*j),(irr::f32)(j + (j * j)+10*j))));
		addChild(_enemyList.back());
	}

	//Create a row of Enemy Asteroids
	for(int k = 0; k < 2; k++)
	{
		_enemyList.push_back(new EnemyAsteroid(irr::core::vector3df(-20,(irr::f32)(k + (k * k)+10*k),(irr::f32)(k + (k * k)+10*k)), irr::core::vector3df(0,0,0.01f)));
		
		addChild(_enemyList.back());
	}

	//Create an enemy ship
	for(int l=0; l<1; l++)
	{
		_enemyList.push_back(new DummyShip(irr::core::vector3df(10,10,10)));
		addChild(_enemyList.back());
	}

}

CollisionTestScene::~CollisionTestScene() {

}
//Debug Key 8
void CollisionTestScene::createRemoveEnemyTest()
{
	if (removeenemytestinitiationcheck)
	{
		//creates 5 enemy asteroids in a row and allows the next key press (8) to work

		_enemyList.push_back(new EnemyAsteroid(irr::core::vector3df(0,0,0), irr::core::vector3df(0.02f,0,0)));
		addChild(_enemyList.back());
		_enemyList.push_back(new EnemyAsteroid(irr::core::vector3df(0,2,0), irr::core::vector3df(0.02f,0,0)));
		addChild(_enemyList.back());
		_enemyList.push_back(new EnemyAsteroid(irr::core::vector3df(0,4,0), irr::core::vector3df(0.02f,0,0)));
		addChild(_enemyList.back());
		_enemyList.push_back(new EnemyAsteroid(irr::core::vector3df(0,6,0), irr::core::vector3df(0.02f,0,0)));
		addChild(_enemyList.back());
		_enemyList.push_back(new EnemyAsteroid(irr::core::vector3df(0,8,0), irr::core::vector3df(0.02f,0,0)));
		addChild(_enemyList.back());
		removeenemytestinitiationcheck = false;
		std::cout << "Test Remove Enemy is initiated, press again to execute \n";
	}
	else
	{
		//removes the second enemy in the list
		//if only pressed once before it will remove the middle
		_enemyList[2]->destroy();
		_enemyList.erase(_enemyList.begin()+2);
		std::cout << "Test Remove Enemy is executed succesfully \n";
		removeenemytestinitiationcheck = true;
	}
}
//Debug Key 9
void CollisionTestScene::RemoveAllEnemies()
{
	//destroys all enemies and removes them from the _enemyList. 
	//changes removetestinitioncheck back to true so that function
	//won't try to remove an already removed enemy
	if (_enemyList.size() != 0)
	{
		for (int i = 0; i < _enemyList.size(); i++)
		{
			_enemyList[i]->destroy();
		}
		_enemyList.clear();
		removeenemytestinitiationcheck = true;
	}
}
