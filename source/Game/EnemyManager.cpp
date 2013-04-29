#include "EnemyManager.h"

#include "Enemy.h"
#include "EnemyManager.h"
#include "EnemyDrone.h"
#include "EnemyFighter.h"
#include "EnemyAsteroid.h"
#include "EnemyPlayer.h"

EnemyManager::EnemyManager(void) 
{
	Network::GetInstance()->AddListener(ENEMY, this);
}

EnemyManager::~EnemyManager(void)
{

}

void EnemyManager::HandleNetworkMessage(NetworkPacket packet)
{
	if(packet.GetType() == PacketType::ENEMY)
	{

	}
}

Enemy* drone1;
EnemyFighter* fighter1;
Enemy* asteroid1;
Enemy* asteroid2;
Enemy* asteroid3;
Enemy* asteroid4;
Enemy* asteroid5;
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
	addComponent(fighter1);

	asteroid1 = new EnemyAsteroid(irr::core::vector3df(50,0,0),vector3df(0,0,0));
	addComponent(asteroid1);
	asteroid2 = new EnemyAsteroid(irr::core::vector3df(50,10,0),vector3df(0,0,0));
	addComponent(asteroid2);
	asteroid3 = new EnemyAsteroid(irr::core::vector3df(50,10,10),vector3df(0,-0.005f,-0.005f));
	addComponent(asteroid3);
	asteroid4 = new EnemyAsteroid(irr::core::vector3df(50,30,0),vector3df(0,-0.005f,0));
	addComponent(asteroid4);
	asteroid5 = new EnemyAsteroid(irr::core::vector3df(50,20,0),vector3df(0,0.005f,0));
	addComponent(asteroid5);
	
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
	this->_enemyList.push_back(asteroid3);
	this->_enemyList.push_back(asteroid4);
	this->_enemyList.push_back(asteroid5);
	this->_enemyList.push_back(player);
}

void EnemyManager::update()
{
	Scene::update();
	NarrowPhaseDetection(this->_enemyList);
	
	for(unsigned int i=0; i<_enemyList.size(); i++) //loop through all asteroids, update these and check for contact with all other asteroids
	{
		

		if(dynamic_cast<EnemyDrone*>(_enemyList[i]))
		{
			_enemyList[i]->steering(irr::core::vector3df(0,1,0));
			if((player->position - _enemyList[i]->position).getLength() <= _enemyList[i]->getLoS())
			{
				_enemyList[i]->inRangeList.push_back(player);
			}
		}else if(dynamic_cast<EnemyFighter*>(_enemyList[i]))
		{
			_enemyList[i]->steering(irr::core::vector3df(0,-1,0));
			if((player->position - _enemyList[i]->position).getLength() <= _enemyList[i]->getLoS())
			{
				_enemyList[i]->inRangeList.push_back(player);
			}
		}
	}
}

/*
#define UNIFORMSIZE 10
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
void EnemyManager::LaserNarrowPhase(array<Enemy*> _enput, array<Laser*> _laput)
{
	for (int i = 0; i < (int)(_laput.size()); i++)
	{
		for(int j = 0; j < (int)(_enput.size()); j++)
		{
			float distance = _laput[i]->position.getDistanceFrom(_enput[j]->position);
			if (distance < (_enput[j]->getRadius()))
			{
				_laput[i]->contactResolver(_enput[j]);
			}
		}
	}
}

void EnemyManager::NarrowPhaseDetection(array<Enemy*> _input)
{
	array<Laser*> laserlist;
	for(int i = 0; i < (int)(_input.size()); i++)
	{
		for(int j = i; j < (int)(_input.size()); j++)
		{
			if(i != j)
			{
				float distance = _input[i]->position.getDistanceFrom(_input[j]->getPosition());
				if (distance < (_input[i]->getOuterRadius() + _input[j]->getOuterRadius()))
				{
					if (distance < (_input[i]->getRadius() + _input[j]->getRadius() ) )
					{
						_input[i]->contactResolverA(_input[j]);
						continue;
					}
					vector3df box1[8];
					vector3df box2[8];

					box1[0] = vector3df(_input[i]->getPosition().X-_input[i]->getRadius(),_input[i]->getPosition().Y+_input[i]->getRadius(),_input[i]->getPosition().Z+_input[i]->getRadius());
					box1[1] = vector3df(_input[i]->getPosition().X+_input[i]->getRadius(),_input[i]->getPosition().Y-_input[i]->getRadius(),_input[i]->getPosition().Z+_input[i]->getRadius());
					box1[2] = vector3df(_input[i]->getPosition().X+_input[i]->getRadius(),_input[i]->getPosition().Y+_input[i]->getRadius(),_input[i]->getPosition().Z+_input[i]->getRadius());
					box1[3] = vector3df(_input[i]->getPosition().X-_input[i]->getRadius(),_input[i]->getPosition().Y-_input[i]->getRadius(),_input[i]->getPosition().Z+_input[i]->getRadius());
					box1[4] = vector3df(_input[i]->getPosition().X-_input[i]->getRadius(),_input[i]->getPosition().Y+_input[i]->getRadius(),_input[i]->getPosition().Z-_input[i]->getRadius());
					box1[5] = vector3df(_input[i]->getPosition().X+_input[i]->getRadius(),_input[i]->getPosition().Y-_input[i]->getRadius(),_input[i]->getPosition().Z-_input[i]->getRadius());
					box1[6] = vector3df(_input[i]->getPosition().X+_input[i]->getRadius(),_input[i]->getPosition().Y+_input[i]->getRadius(),_input[i]->getPosition().Z-_input[i]->getRadius());
					box1[7] = vector3df(_input[i]->getPosition().X-_input[i]->getRadius(),_input[i]->getPosition().Y-_input[i]->getRadius(),_input[i]->getPosition().Z-_input[i]->getRadius());

					box2[0] = vector3df(_input[j]->getPosition().X-_input[j]->getRadius(),_input[j]->getPosition().Y+_input[j]->getRadius(),_input[j]->getPosition().Z+_input[j]->getRadius());
					box2[1] = vector3df(_input[j]->getPosition().X+_input[j]->getRadius(),_input[j]->getPosition().Y-_input[j]->getRadius(),_input[j]->getPosition().Z+_input[j]->getRadius());
					box2[2] = vector3df(_input[j]->getPosition().X+_input[j]->getRadius(),_input[j]->getPosition().Y+_input[j]->getRadius(),_input[j]->getPosition().Z+_input[j]->getRadius());
					box2[3] = vector3df(_input[j]->getPosition().X-_input[j]->getRadius(),_input[j]->getPosition().Y-_input[j]->getRadius(),_input[j]->getPosition().Z+_input[j]->getRadius());
					box2[4] = vector3df(_input[j]->getPosition().X-_input[j]->getRadius(),_input[j]->getPosition().Y+_input[j]->getRadius(),_input[j]->getPosition().Z-_input[j]->getRadius());
					box2[5] = vector3df(_input[j]->getPosition().X+_input[j]->getRadius(),_input[j]->getPosition().Y-_input[j]->getRadius(),_input[j]->getPosition().Z-_input[j]->getRadius());
					box2[6] = vector3df(_input[j]->getPosition().X+_input[j]->getRadius(),_input[j]->getPosition().Y+_input[j]->getRadius(),_input[j]->getPosition().Z-_input[j]->getRadius());
					box2[7] = vector3df(_input[j]->getPosition().X-_input[j]->getRadius(),_input[j]->getPosition().Y-_input[j]->getRadius(),_input[j]->getPosition().Z-_input[j]->getRadius());
					
					for (int k = 0; k < 8; k++)
					{
						for (int l = 0; l < 8; l++)
						{
							if (box1[k].X > box2[l].X - _input[i]->getRadius()||
								box1[k].Y > box2[l].Y - _input[i]->getRadius()||
								box1[k].Z > box2[l].Z - _input[i]->getRadius()||
								box2[k].X > box1[l].X - _input[i]->getRadius()||
								box2[k].Y > box1[l].Y - _input[i]->getRadius()||
								box2[k].Z > box1[l].Z - _input[i]->getRadius() 
								)
							{
								_input[i]->contactResolverA(_input[j]);
							}
						}
					}

					/*
					if (distance < (_input[i]->getRadius() + _input[j]->getOuterRadius()))
					{
						_input[i]->contactResolverA(_input[j]);
					}
					if (distance < (_input[j]->getRadius() + _input[i]->getOuterRadius()))
					{
						_input[i]->contactResolverA(_input[j]);
					}
					*/
				}
				else
				{
					_input[i]->setRadius(_input[i]->getOriginalRadius());
				}
			}
		}
		if(dynamic_cast<EnemyFighter*>(_input[i]))
		{
			EnemyFighter* temp = (EnemyFighter*) _input[i];
			if (!temp->GetLasers().empty())
			{
				for (int k = 0; k < temp->GetLasers().size(); k++)
				{
					laserlist.push_back(temp->GetLasers()[k]);
				}
			}
		}
	}
	if (!laserlist.empty())
	{
		LaserNarrowPhase(_input, laserlist);
	}
 //float distance = position.getDistanceFrom(input->getPosition());
 //float radii = input->getRadius() + radius_;
 //if (distance < radii)
 //{
 // contactResolverB();
 //}
}