#include "EnemyAsteroid.h"
#include "Engine/Entity.h"

EnemyAsteroid::EnemyAsteroid(irr::core::vector3df position): Enemy()
{
	this->setVisualWithPath("../assets/Models/Space_Asteroid.dae");
	this->setPosition(position);
	this->setHealth(25);
	this->setAgility(1);
	this->setMaxSpeed(100);	
}


EnemyAsteroid::~EnemyAsteroid(void)
{

}

void EnemyAsteroid::linearpath()
{
	Enemy::update();
}