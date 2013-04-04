#include "EnemyAsteroid.h"
#include "Engine/Entity.h"
#include <iostream>

EnemyAsteroid::EnemyAsteroid(irr::core::vector3df _position): Enemy()
{
	this->setVisualWithPath("../assets/Models/Space_Asteroid.dae");
	this->setPosition(_position);
	this->setHealth(25);
	this->setAgility(1);
	this->setMaxSpeed(100);		
}

EnemyAsteroid::~EnemyAsteroid(void)
{

}

void EnemyAsteroid::update()
{
	Enemy::update();
}

void EnemyAsteroid::lupdate(Enemy* enemy, vector3df speed)
{	
	//this->setVelocity(speed);
	//this->setPosition(vector3df(this->getVelocity()+this->getPosition()));
	Enemy::contactGenerator(enemy);
	update();
	//std::cout<< " " << this->getPosition().Y;
}