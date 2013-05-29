#include "EnemyManager.h"

using namespace irr;
using namespace irr::core;

EnemyManager::EnemyManager(irr::scene::ISceneManager* smgr) : Composite("EnemyManager")
{
	_smgr = smgr;
}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::init() {
	createEnemies();
}

void EnemyManager::createEnemies()
{
	/*
	* This is SCREAMING MEMORY LEAKS.
	* Refactor or remove.
	*/
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

	drone1 = new EnemyDrone(_smgr, vector3df(0,0,40));
	drone1->setVelocity(&vector3df(0.0005f,0,0));
	drone1->setRotation(&vector3df(0,1,0));
	addComponent(drone1);

	fighter1 = new EnemyFighter(_smgr, vector3df(100,0,0));
	fighter1->setVelocity(&vector3df(0.1f,0,0));
	addComponent(fighter1);

	asteroid1 = new EnemyAsteroid(_smgr, vector3df(50,0,0), vector3df(0,0,0));
	addComponent(asteroid1);

	asteroid2 = new EnemyAsteroid(_smgr, vector3df(50,10,0), vector3df(0,0,0));
	addComponent(asteroid2);

	asteroid3 = new EnemyAsteroid(_smgr, vector3df(50,10,10), vector3df(0,-0.005f,-0.005f));
	addComponent(asteroid3);

	asteroid4 = new EnemyAsteroid(_smgr, vector3df(50,30,0), vector3df(0,-0.005f,0));
	addComponent(asteroid4);

	asteroid5 = new EnemyAsteroid(_smgr, vector3df(50,20,0), vector3df(0,0.005f,0));
	addComponent(asteroid5);

	////kamikaze enemy
	kamikaze1 = new EnemyDrone(_smgr, vector3df(30,30,30));
	kamikaze1->setVelocity(&vector3df(0.0005f,0,0));
	addComponent(kamikaze1);

	kamikaze2 = new EnemyDrone(_smgr, vector3df(150,150,150));
	addComponent(kamikaze2);

	kamikaze3 = new EnemyDrone(_smgr, vector3df(-50,-50,-50));
	addComponent(kamikaze3);

	kamikaze4 = new EnemyDrone(_smgr, vector3df(-150,-150,-150));
	addComponent(kamikaze4);

	kamikaze5 = new EnemyDrone(_smgr, vector3df(25,25,250));
	addComponent(kamikaze5);

	//dummyplayer
	player = new EnemyPlayer(_smgr, vector3df(0,0,10), vector3df(0,0.0f,0));
	addComponent(player);
}

void EnemyManager::update() {
	narrowPhaseDetection(components);

	for(std::list<Component*>::iterator it = components.begin(); it != components.end(); it++)
	{
		if(dynamic_cast<EnemyDrone*>((*it)))
		{
			dynamic_cast<EnemyDrone*>((*it))->steering(vector3df(0,1,0), *player->getPosition());
			if((*player->getPosition() - *dynamic_cast<EnemyDrone*>((*it))->getPosition()).getLength() <= dynamic_cast<EnemyDrone*>((*it))->getLoS())
			{
				dynamic_cast<EnemyDrone*>((*it))->inRangeList.push_back(player);
			}
		}else if(dynamic_cast<EnemyFighter*>((*it)))
		{
			dynamic_cast<EnemyFighter*>((*it))->steering(vector3df(0,-1,0), *player->getPosition());
			if((*player->getPosition() - *dynamic_cast<EnemyFighter*>((*it))->getPosition()).getLength() <= dynamic_cast<EnemyFighter*>((*it))->getLoS())
			{
				dynamic_cast<EnemyFighter*>((*it))->inRangeList.push_back(player);
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

void EnemyManager::laserNarrowPhase(std::list<Component*> _input, std::list<Laser*> _laput)
{
	for(std::list<Component*>::iterator it = _input.begin(); it != _input.end(); it++)
	{
		for(std::list<Laser*>::iterator lt = _laput.begin(); lt != _laput.end(); lt++)
		{
			float distance = ((*lt)->getPosition())->getDistanceFrom(*dynamic_cast<Enemy*>(*it)->getPosition());

			if (distance < (dynamic_cast<Enemy*>(*it)->getRadius()->X))
			{
				(*lt)->contactResolver(dynamic_cast<Enemy*>(*it));
			}
		}
	}
}

void EnemyManager::narrowPhaseDetection(std::list<Component*> _input)
{
	std::list<Laser*> laserlist;

	for(std::list<Component*>::iterator it = _input.begin(); it != _input.end(); it++)
	{
		for(std::list<Component*>::iterator it2 = _input.begin(); it2 != _input.end(); it2++)
		{
			Enemy* tempEnemyA = dynamic_cast<Enemy*>(*it);
			Enemy* tempEnemyB = dynamic_cast<Enemy*>(*it2);

			if(tempEnemyA != tempEnemyB)
			{
				float distance = tempEnemyA->getPosition()->getDistanceFrom(*tempEnemyB->getPosition());
				if (distance < (tempEnemyA->getOuterRadius() + tempEnemyB->getOuterRadius()))
				{
					if (distance < (tempEnemyA->getRadius()->X + tempEnemyB->getRadius()->X) )
					{
						tempEnemyA->contactResolver(tempEnemyB);
						continue;
					}

					vector3df* box1 = createBoundingBox(tempEnemyA);
					vector3df* box2 = createBoundingBox(tempEnemyB);

					for (int k = 0; k < 8; k++)
					{
						for (int l = 0; l < 8; l++)
						{
							if (box1[k].X > box2[l].X - tempEnemyA->getRadius()->X ||
								box1[k].Y > box2[l].Y - tempEnemyA->getRadius()->X ||
								box1[k].Z > box2[l].Z - tempEnemyA->getRadius()->X ||
								box2[k].X > box1[l].X - tempEnemyA->getRadius()->X ||
								box2[k].Y > box1[l].Y - tempEnemyA->getRadius()->X ||
								box2[k].Z > box1[l].Z - tempEnemyA->getRadius()->X 
								)
							{
								tempEnemyA->contactResolver(tempEnemyB);
							}
						}
					}
				}
				else
				{
					tempEnemyA->setRadius(tempEnemyA->getOriginalRadius());
				}

			}
		}
	}
}

vector3df* EnemyManager::createBoundingBox(Enemy* object)
{
	vector3df* box = new vector3df[8];

	box[0] = vector3df(object->getPosition()->X - object->getRadius()->X, 
		object->getPosition()->Y + object->getRadius()->X,
		object->getPosition()->Z + object->getRadius()->X);
	box[1] = vector3df(object->getPosition()->X + object->getRadius()->X,
		object->getPosition()->Y - object->getRadius()->X,
		object->getPosition()->Z + object->getRadius()->X);
	box[2] = vector3df(object->getPosition()->X + object->getRadius()->X,
		object->getPosition()->Y + object->getRadius()->X,
		object->getPosition()->Z + object->getRadius()->X);
	box[3] = vector3df(object->getPosition()->X - object->getRadius()->X,
		object->getPosition()->Y - object->getRadius()->X,
		object->getPosition()->Z + object->getRadius()->X);
	box[4] = vector3df(object->getPosition()->X - object->getRadius()->X,
		object->getPosition()->Y + object->getRadius()->X,
		object->getPosition()->Z - object->getRadius()->X);
	box[5] = vector3df(object->getPosition()->X + object->getRadius()->X,
		object->getPosition()->Y - object->getRadius()->X,
		object->getPosition()->Z - object->getRadius()->X);
	box[6] = vector3df(object->getPosition()->X + object->getRadius()->X,
		object->getPosition()->Y + object->getRadius()->X,
		object->getPosition()->Z - object->getRadius()->X);
	box[7] = vector3df(object->getPosition()->X - object->getRadius()->X,
		object->getPosition()->Y - object->getRadius()->X,
		object->getPosition()->Z - object->getRadius()->X);

	return box;
}