#include "EnemyAsteroid.h"

using namespace irr;
using namespace irr::core;

EnemyAsteroid::EnemyAsteroid(irr::scene::ISceneManager* smgr, vector3df position, vector3df velocity) : Enemy(smgr)
{
	setPosition(&position);
	setMaxHealth(25);
	setAgility(1);
	setMaxSpeed(100);	
	setAcceleration(&vector3df(0,0,0));	
	setRadius(1);
	setOriginalRadius(1);
	setOuterRadius(sqrt(getRadius()->X * getRadius()->X) + (getRadius()->X * getRadius()->X));
	setVelocity(&velocity);
	this->_type = Enemy::ASTROID;
}

void EnemyAsteroid::init()
{
	Enemy::init();
}

void EnemyAsteroid::onAdd()
{
	Enemy::onAdd();

	setMesh("../assets/Models/Space_Asteroid.dae");
}

EnemyAsteroid::~EnemyAsteroid(void)
{

}
