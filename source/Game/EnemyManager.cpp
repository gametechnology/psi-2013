#include "EnemyManager.h"
#include "Enemy.h"

EnemyManager::EnemyManager(void) : Entity(parent)
{
	
}
EnemyManager::~EnemyManager(void)
{
}

void EnemyManager::createEnemies()
{
	//this->_enemies = array<Enemy>();
	for(int i = 0; i < 10;i++)
	{
	/*	Enemy* enemy = new Enemy();
		enemy->createNode("../assets/Models/Cube.3ds");
		this->_posX = rand()%(30);
		this->_posY = rand()%(30);
		this->_posZ = rand()%(30);
		enemy->setPosition(irr::core::vector3df(this->_posX,this->_posY,this->_posZ));
		enemy->position = enemy->getPosition();*/
		//this->_enemies.insert(enemy);
	}
}