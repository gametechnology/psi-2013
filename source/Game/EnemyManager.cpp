#include "EnemyManager.h"

#include "Enemy.h"
#include "EnemyManager.h"
#include "EnemyDrone.h"
#include "EnemyFighter.h"
#include "EnemyAsteroid.h"
#include "EnemyPlayer.h"

EnemyManager::EnemyManager(void) 
{
	createEnemies();
}

EnemyManager::~EnemyManager(void)
{

}

Enemy* drone1;
EnemyFighter* fighter1;
Enemy* asteroid1;
Enemy* asteroid2;
EnemyDrone* kamikaze1;
EnemyDrone* kamikaze2;
EnemyDrone* kamikaze3;
EnemyDrone* kamikaze4;
EnemyDrone* kamikaze5;
Enemy* player;

EnemyDrone* test;

void EnemyManager::createEnemies()
{
	this->_enemyList = array<Enemy*>();

	drone1 = new EnemyDrone(irr::core::vector3df(0,0,40));
	drone1->setVelocity(vector3df(0.0005f,0,0));
	drone1->setRotation(irr::core::vector3df(0,1,0));
	addComponent(drone1);
	fighter1 = new EnemyFighter(irr::core::vector3df(100,0,0));
	fighter1->setVelocity(vector3df(0.0005f,0,0));
	fighter1->setRotation(irr::core::vector3df(0,1,0));
	addComponent(fighter1);
	asteroid1 = new EnemyAsteroid(irr::core::vector3df(50,0,0),vector3df(0,0.001f,0));
	addComponent(asteroid1);
	asteroid2 = new EnemyAsteroid(irr::core::vector3df(50,10,0),vector3df(0,-0.001f,0));
	addComponent(asteroid2);
	
	//kamikaze enemy
	kamikaze1 = new EnemyDrone(irr::core::vector3df(30,30,30));
	kamikaze1->setVelocity(vector3df(0.0005f,0,0));
	addComponent(kamikaze1);
	kamikaze2 = new EnemyDrone(irr::core::vector3df(150,150,150));
	addComponent(kamikaze2);
	kamikaze3 = new EnemyDrone(irr::core::vector3df(-50,-50,-50));
	addComponent(kamikaze3);
	kamikaze4 = new EnemyDrone(irr::core::vector3df(-150,-150,-150));
	addComponent(kamikaze4);
	kamikaze5 = new EnemyDrone(irr::core::vector3df(25,25,250));
	addComponent(kamikaze5);

	//dummyplayer
	player = new EnemyPlayer(irr::core::vector3df(0,0,10),vector3df(0,0.0f,0));
	addComponent(player);

	
	this->_enemyList.push_back(drone1);
	this->_enemyList.push_back(kamikaze1);
	this->_enemyList.push_back(kamikaze2);
	this->_enemyList.push_back(kamikaze3);
	this->_enemyList.push_back(kamikaze4);
	this->_enemyList.push_back(kamikaze5);
	this->_enemyList.push_back(fighter1);
	this->_enemyList.push_back(asteroid1);
	this->_enemyList.push_back(asteroid2);
	this->_enemyList.push_back(player);
}

void EnemyManager::update()
{
	Scene::update();
	NarrowPhaseDetection(this->_enemyList);

	for(unsigned int i=0; i<_enemyList.size(); i++) //loop through all asteroids, update these and check for contact with all other asteroids
	{
		//for(unsigned int j=0; j<_enemyList.size(); j++)
		//{
		//	if(j!=i)
		//	{
		//		if(!dynamic_cast<EnemyFighter*>(_enemyList[i]) && !dynamic_cast<EnemyFighter*>(_enemyList[j]))
		//			this->_enemyList[i]->contactGenerator(_enemyList[j]);	
		//	}
		//}

		if(dynamic_cast<EnemyDrone*>(_enemyList[i]))
		{
			_enemyList[i]->steering();
			if((player->position - _enemyList[i]->position).getLength() <= _enemyList[i]->getLoS())
			{
				_enemyList[i]->inRangeList.push_back(player);
			}
		}else if(dynamic_cast<EnemyFighter*>(_enemyList[i]))
		{
			_enemyList[i]->steering();
			if((player->position - _enemyList[i]->position).getLength() <= _enemyList[i]->getLoS())
			{
				_enemyList[i]->inRangeList.push_back(player);
			}
		}
	}
}

#define UNIFORMSIZE 10

/*
void EnemyManager::BroadPhaseDetection()
{
	vector3df max = vector3df(0,0,0);
	vector3df min = vector3df(0,0,0);

	for (int i = 0; this->_enemyList.size(); i++)
	{
		if (this->_enemyList[i]->position.X > max.X)
		{
			max.X = this->_enemyList[i]->position.X;
		}
		if (this->_enemyList[i]->position.Y > max.Y)
		{
			max.Y = this->_enemyList[i]->position.Y;
		}
		if (this->_enemyList[i]->position.Z > max.Z)
		{
			max.Z = this->_enemyList[i]->position.Z;
		}

		if (this->_enemyList[i]->position.X < min.X)
		{
			min.X = this->_enemyList[i]->position.X;
		}
		if (this->_enemyList[i]->position.Y < min.Y)
		{
			min.Y = this->_enemyList[i]->position.Y;
		}
		if (this->_enemyList[i]->position.Z < min.Z)
		{
			min.Z = this->_enemyList[i]->position.Z;
		}
	}

	min *= min;
	max *= max;
	
	//TODO take root of all min max xyz's

	unsigned int intervalsx = (min.X + max.X)/UNIFORMSIZE;
	unsigned int intervalsy = (min.Y + max.Y)/UNIFORMSIZE;
	unsigned int intervalsz = (min.Z + max.Z)/UNIFORMSIZE;
	
	array<Enemy*> spaces;

	for (int i = 0; this->_enemyList.size(); i++)
	{
		for (int j = 0; j < intervalsx; j++)			//x = j
		{
			if (this->_enemyList[i]->position.X > (intervalsx*j) && this->_enemyList[i]->position.X < intervalsx*(j+1))
			{
				for (int k = 0; k < intervalsy; k++)		//y = k
				{
					if (this->_enemyList[i]->position.Y > (intervalsy*k) && this->_enemyList[i]->position.Y < intervalsy*(k+1))
					{
						for (int l = 0; l < intervalsz; l++)	//z = l
						{
							if (this->_enemyList[i]->position.Z > (intervalsz*l) && this->_enemyList[i]->position.Z < intervalsz*(l+1))
							{

							}
						}
					}
				}
			}	
		}
	}

	for (int i = 0; i < 10; i++)
	{
		NarrowPhaseDetection();
	}
}
*/

void EnemyManager::NarrowPhaseDetection(array<Enemy*> _input)
{
	for(int i = 0; i < _input.size(); i++)
	{
		for(int j = i; j < _input.size(); j++)
		{
			if(i != j)
			{
				float distance = _input[i]->position.getDistanceFrom(_input[j]->getPosition());
				if (distance < (_input[i]->getOuterRadius() + _input[j]->getOuterRadius()))
				{
					if (distance < (_input[i]->getRadius() + _input[j]->getRadius()))
					{
						_input[i]->contactResolverA(_input[j]);
					}
					if (distance < (_input[i]->getRadius() + _input[j]->getOuterRadius()))
					{
						_input[i]->contactResolverA(_input[j]);
					}
					if (distance < (_input[j]->getRadius() + _input[i]->getOuterRadius()))
					{
						_input[i]->contactResolverA(_input[j]);
					}
				}
			}
		}
		_input[i]->setRadius(_input[i]->getOriginalRadius());
	}
 //float distance = position.getDistanceFrom(input->getPosition());
 //float radii = input->getRadius() + radius_;
 //if (distance < radii)
 //{
 // contactResolverB();
 //}
}