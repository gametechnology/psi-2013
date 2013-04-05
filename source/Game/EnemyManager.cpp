#include "EnemyManager.h"

#include "Enemy.h"
#include "EnemyManager.h"
#include "EnemyDrone.h"
#include "EnemyFighter.h"
#include "EnemyAsteroid.h"

EnemyManager::EnemyManager(void) 
{

}

EnemyManager::~EnemyManager(void)
{

}

Enemy* drone1;
Enemy* fighter1;
Enemy* asteroid1;
Enemy* asteroid2;
Enemy* enemy1;

void EnemyManager::createEnemies()
{
	this->_enemyList = array<Enemy*>();

	drone1 = new EnemyDrone(irr::core::vector3df(0,0,10));
	drone1->setVelocity(vector3df(0.005f,0,0));
	drone1->setRotation(irr::core::vector3df(0,1,0));
	addComponent(drone1);
	fighter1 = new EnemyFighter(irr::core::vector3df(100,0,0));
	fighter1->setVelocity(vector3df(0.005f,0,0));
	fighter1->setRotation(irr::core::vector3df(0,1,0));
	addComponent(fighter1);
	asteroid1 = new EnemyAsteroid(irr::core::vector3df(0,0,0),vector3df(0,0.005f,0));
	addComponent(asteroid1);
	asteroid2 = new EnemyAsteroid(irr::core::vector3df(0,10,0),vector3df(0,-0.005f,0));
	addComponent(asteroid2);
	
	this->_enemyList.push_back(drone1);
	this->_enemyList.push_back(fighter1);
	this->_enemyList.push_back(asteroid1);
	this->_enemyList.push_back(asteroid2);

	
}

void EnemyManager::update()
{
	drone1->steering();
	drone1->update();
	fighter1->steering();
	fighter1->update();
	asteroid1->update();
	asteroid2->update();
	asteroid1->contactGenerator(asteroid2);
	asteroid2->contactGenerator(asteroid1);

	/*for(unsigned int i=0; i<_enemyasteroids.size(); i++) //loop through all asteroids, update these and check for contact with all other asteroids
	{
		_enemyasteroids[i].update();

		for(unsigned int j=0; j<_enemyasteroids.size(); j++)
		{
			if(j!=i)
			{
				_enemyasteroids[i].contactGenerator(&_enemyasteroids[j]);	
			}
		}
		for(unsigned int j=0; j<_enemydrones.size(); j++)
		{
			if(j!=i)
			{
				_enemyasteroids[i].contactGenerator(&_enemydrones[j]);	
			}
		}
		for(unsigned int j=0; j<_enemyfighters.size(); j++)
		{
			if(j!=i)
			{
				_enemyasteroids[i].contactGenerator(&_enemyfighters[j]);	
			}
		}
	}*/
}