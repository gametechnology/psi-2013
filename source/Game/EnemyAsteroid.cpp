#include "EnemyAsteroid.h"
#include "Engine/Entity.h"
#include <iostream>

EnemyAsteroid::EnemyAsteroid(irr::core::vector3df position, vector3df speed): Enemy()
{
	this->setVisualWithPath("../assets/Models/Space_Asteroid.dae");
	this->setPosition(position);
	this->setMaxHealth(25);
	this->setAgility(1);
	this->setMaxSpeed(100);	
	this->setAccelaration(vector3df(0,0,0));	
	this->setRadius(1);
	this->setVelocity(speed);
}

EnemyAsteroid::~EnemyAsteroid(void)
{

}
void EnemyAsteroid::update()
{
	Enemy::update();
}
