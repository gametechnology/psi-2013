#include "EnemyAsteroid.h"
#include "Engine/Entity.h"
#include "Engine/Collision.h"
#include <iostream>
#include "Laser.h"

EnemyAsteroid::EnemyAsteroid(irr::core::vector3df position, vector3df velocity): Enemy()
{
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

void EnemyAsteroid::init()
{
	Enemy::init();
}

void EnemyAsteroid::onAdd()
{
	Enemy::onAdd();

	this->setVisualWithPath("../assets/Models/Space_Asteroid.dae");
	Collision* collision = new Collision();
	addComponent(collision);
}

EnemyAsteroid::~EnemyAsteroid(void)
{

}

void EnemyAsteroid::contactResolverA(Entity* input)
{
		//std::printf("HIT on ASTEROID! \n");
		Entity::contactResolverA(input);
	
}