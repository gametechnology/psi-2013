#include "EnemyAsteroid.h"
#include "Engine/Entity.h"
#include <iostream>

EnemyAsteroid::EnemyAsteroid(irr::core::vector3df position, vector3df velocity): Enemy()
{
	this->setVisualWithPath("../assets/Models/Space_Asteroid.dae");
	this->setPosition(position);
	this->setMaxHealth(25);
	this->setAgility(1);
	this->setMaxSpeed(100);	
	this->setAccelaration(vector3df(0,0,0));	
	this->setRadius(1);
	this->setOriginalRadius(1);
	this->setOuterRadius(sqrt((this->getRadius()*this->getRadius())+(this->getRadius()*this->getRadius())));
	this->setVelocity(velocity);
	this->_type = Enemy::ASTROID;
}

EnemyAsteroid::~EnemyAsteroid(void)
{

}
