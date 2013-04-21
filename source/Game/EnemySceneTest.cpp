#include "EnemySceneTest.h"

#include "Skybox.h"
#include "EnemyManager.h"
#include "RandomGenerator.h"

NetworkPacket packet(ENEMY);

EnemySceneTest::EnemySceneTest(void)
{
	Network::GetInstance()->AddListener(ENEMY, this);
	EnemySceneTest::_enemyList = array<Enemy*>();
}


EnemySceneTest::~EnemySceneTest(void)
{
	Scene::~Scene();
}

void EnemySceneTest::HandleNetworkMessage(NetworkPacket packet)
{
	if(packet.GetType() == ENEMY)
	{
		if(!Network::GetInstance()->IsServer())
		{
			int size;
			array<int> enemyIds = array<int>();
			array<int> enemyType = array<int>();
			array<vector3df> enemyPositions = array<vector3df>();
			array<vector3df> enemyVelocities = array<vector3df>();
			array<vector3df> enemyRotations = array<vector3df>();
			array<bool> enemiesAreAlive = array<bool>();
			array<int> enemiesHealth = array<int>();

			packet >> size >> enemyIds >> enemyType >> enemyPositions >> enemyVelocities >> 
				enemyRotations >> enemiesAreAlive >> enemiesHealth;

			if(size != _enemyList.size())
			{
				for(int i = 0; i < _enemyList.size(); i++)
				{
					if(!enemyIds.binary_search(_enemyList[i]->getId()))
					{
						_enemyList[i]->destroy();
					}
				}

				if(size > _enemyList.size())
				{
					for(int i = 0; i < size; i++)
					{
						for(int j = 0; j < _enemyList.size(); j++)
						{
							if(enemyIds[i] == _enemyList[j]->getId())
								continue;
						}

						Enemy* enemy;
						switch((Enemy::EnemyType)enemyType[i])
						{
						case Enemy::ASTROID:
							enemy = new EnemyAsteroid(enemyPositions[i], enemyVelocities[i]);
							break;
						case Enemy::DRONE:
							enemy = new EnemyDrone(enemyPositions[i]);
							break;
						case Enemy::FIGHTER:
							enemy = new EnemyFighter(enemyPositions[i]);
							break;
						}

						enemy->setId(enemyIds[i]);
						enemy->setVelocity(enemyVelocities[i]);
						enemy->setRotation(enemyRotations[i]);
						enemy->setHealth(enemiesHealth[i]);

						_enemyList.push_back(enemy);
					}
				}
			}
		}
			
	}
}


void EnemySceneTest::init()
{
	//EnemyManager* enemymanager;
	smgr = Game::getSceneManager();
	camera = smgr->addCameraSceneNodeFPS();
	this->light = smgr->addLightSceneNode(0,vector3df(5000,5000,5000),SColor(100,100,100,255),100000);
	//enemymanager = new EnemyManager();	
	//enemymanager->createEnemies();
	//addComponent(enemymanager);

	if(Network::GetInstance()->IsServer())
	{
		createEnemies();
	}
}

int timer = 0;

void EnemySceneTest::update()
{
	Scene::update();
	if(timer >= 500)
	{
		if(Network::GetInstance()->IsServer())
		{
			array<int> enemyIds = array<int>();
			array<int> enemyType = array<int>();
			array<vector3df> enemyPositions = array<vector3df>();
			array<vector3df> enemyVelocities = array<vector3df>();
			array<vector3df> enemyRotations = array<vector3df>();
			array<bool> enemiesAreAlive = array<bool>();
			array<int> enemiesHealth = array<int>();

			for(int i = 0; i < EnemySceneTest::_enemyList.size(); i++)
			{
				enemyIds.push_back(_enemyList[i]->getId());
				enemyType.push_back(_enemyList[i]->getType());
				enemyPositions.push_back(_enemyList[i]->getPosition());
				enemyVelocities.push_back(_enemyList[i]->getVelocity());
				enemyRotations.push_back(_enemyList[i]->getRotation());
				enemiesAreAlive.push_back(_enemyList[i]->isAlive());
				enemiesHealth.push_back(_enemyList[i]->getHealth());
			}

			packet << _enemyList.size() << enemyIds << enemyType << enemyPositions << enemyVelocities << 
				enemyRotations << enemiesAreAlive << enemiesHealth;

			Network::GetInstance()->SendServerPacket(packet);
		}
		timer = 0;
	}
	timer++;
}


void EnemySceneTest::createEnemies()
{
	this->_enemyList = array<Enemy*>();

	for(int i = 0; i < 20; i++)
	{
		_enemyList.push_back(new EnemyDrone(irr::core::vector3df(0,0,RandomGenerator::getRandomInt(10, 1))));
	}

	for(int j = 0; j < _enemyList.size(); j++)
	{
		addComponent(_enemyList[j]);
	}
}