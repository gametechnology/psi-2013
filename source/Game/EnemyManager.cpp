#include "EnemyManager.h"

#include "Enemy.h"
#include "EnemyManager.h"
#include "EnemyDrone.h"
#include "EnemyFighter.h"
#include "EnemyAsteroid.h"
#include "EnemyPlayer.h"

EnemyManager::EnemyManager(void) 
{

}

EnemyManager::~EnemyManager(void)
{

}

Enemy* drone1;
EnemyFighter* fighter1;
Enemy* asteroid1;
Enemy* asteroid2;
EnemyDrone* kamikaze1;
Enemy* player;

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
	
	//kamikaze enemy
	kamikaze1 = new EnemyDrone(irr::core::vector3df(50,50,50));
	addComponent(kamikaze1);

	//dummyplayer
	player = new EnemyPlayer(irr::core::vector3df(0,0,10),vector3df(0,0.0f,0));
	addComponent(player);

	
	this->_enemyList.push_back(drone1);
	this->_enemyList.push_back(fighter1);
	this->_enemyList.push_back(asteroid1);
	this->_enemyList.push_back(asteroid2);
	this->_enemyList.push_back(player);
	
	
}

void EnemyManager::update()
{
	Scene::update();
	//drone1->steering();
	fighter1->steering();
	fighter1->SetTarget(player->getPosition());
	kamikaze1->steering();	

	if((player->position - fighter1->position).getLength()>10 && (player->position - fighter1->position).getLength()<=fighter1->getLoS())
	{
		fighter1->chase(player->getPosition());
	}	
	if((player->position - kamikaze1->position).getLength()<kamikaze1->getLoS())
	{
		kamikaze1->chase(player->getPosition());
	}
	

	for(unsigned int i=0; i<_enemyList.size(); i++) //loop through all asteroids, update these and check for contact with all other asteroids
	{
		//this->_enemyList[i]->update();

		for(unsigned int j=0; j<_enemyList.size(); j++)
		{
			if(j!=i)
			{
				this->_enemyList[i]->contactGenerator(_enemyList[j]);	
			}
		}

		if(dynamic_cast<EnemyDrone*>(_enemyList[i]))
		{
			if((player->position - _enemyList[i]->position).getLength() <= _enemyList[i]->getLoS())
			{
				_enemyList[i]->inRangeList.push_back(player);
			}
		}else if(dynamic_cast<EnemyFighter*>(_enemyList[i]))
		{
			if((player->position - _enemyList[i]->position).getLength() <= _enemyList[i]->getLoS())
			{
				_enemyList[i]->inRangeList.push_back(player);
			}
		}
	}
}