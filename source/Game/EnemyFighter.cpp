#include "EnemyFighter.h"
#include "Engine/Entity.h"

EnemyFighter::EnemyFighter(irr::core::vector3df position): Enemy()
{
	this->setVisualWithPath("../assets/Models/Space_Fighter.dae");
	this->setPosition(position);
	this->setMaxHealth(50);
	this->setAgility(2);
	this->setMaxSpeed(400);
	this->setAccelaration(vector3df(45,0,0));
	this->setLoS(4800);

	EnemyFighter::inRangeList = array<Entity*>();
	EnemyFighter::stateSwitch = new StateSwitchFighter(StateSwitch::STATE_WANDER,this);

	this->loadLaser();
}

void EnemyFighter::chase(vector3df target)
{
	Enemy::chase(target);
}

void EnemyFighter::SetTarget(vector3df target)
{
	this->_target = target;
}

void EnemyFighter::loadLaser()
{
	this->_nrLasers = 5;
	this->_laser = new Laser[this->_nrLasers];
	this->_curLaser = 0;
	this->_fireTime = 0;

	for (int i = 0; i < this->_nrLasers; i++)
	{
		Game::getCurrentScene()->addComponent(&this->_laser[i]);
	}
}

void EnemyFighter::update()
{
	EnemyFighter::stateSwitch->updateState();
	EnemyFighter::inRangeList.clear();

	//Should be activated when in current state
	this->_fireTime++;

	if(this->_fireTime >= 400)
	{
		//fire laser to target
		this->fireLaserAt(this->_target);
		this->_fireTime = 0;
	}
	this->_laser[this->_curLaser].update();

	Enemy::update();
}

EnemyFighter::~EnemyFighter(void)
{
	delete EnemyFighter::stateSwitch;

	Entity::~Entity();
}

void EnemyFighter::fireLaserAt(vector3df target)
{
	this->_laser[this->_curLaser].fire(this, target, 1.0f);
	this->_curLaser++;
	
	if(this->_curLaser >= 5)
	{
		this->_curLaser = 0;
	}
}

