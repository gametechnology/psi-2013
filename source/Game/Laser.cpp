#include "Laser.h"
#include <iostream>

Laser::Laser() : Entity(parent)
{
	this->visible = false;
	this->isAlive = false;
	this->createNode("../assets/Models/laser.3ds");
	this->_currentLife = 0;
	this->_timeofLife = 100;
}

Laser::~Laser()
{
	Entity::~Entity();
}


void Laser::fire(Entity* parent, vector3df target, f32 speed)
{
	this->isAlive = true;
	this->position = parent->position;

	this->orientation = parent->orientation;
	this->orientation.Y += 90;
	this->visible = true;	

	this->_direction = target - this->position;
	this->_direction.normalize();

	this->velocity = this->_direction * speed;
}

void Laser::update()
{
	if(this->isAlive)
	{
		this->_currentLife++;
		if(this->_currentLife >= this->_timeofLife)
		{
			this->velocity = vector3df(0,0,0);
			this->visible = false;
			this->_currentLife = 0;
			this->isAlive = false;
		}
	}

	Entity::update();
}