#include "EnemyFighter.h"
#include "Engine/Entity.h"
#include "Engine/Collision.h"

EnemyFighter::EnemyFighter(irr::core::vector3df position): Enemy()
{
	this->setPosition(position);
	this->setMaxHealth(50);
	this->setAgility(2);
	this->setMaxSpeed(400);
	this->setRadius(1);
	this->setOriginalRadius(1);
	this->setOuterRadius(1);
	this->setAccelaration(vector3df(45,0,0));
	this->setLoS(4800);
	this->_type = Enemy::FIGHTER;

}

void EnemyFighter::init()
{
	Enemy::init();

	EnemyFighter::inRangeList = vector<Entity*>();
	EnemyFighter::stateSwitch = new StateSwitchFighter(StateSwitch::STATE_OFFENSIVE,this);
}

void EnemyFighter::onAdd() 
{
	Enemy::onAdd();
	
	this->setVisualWithPath("../assets/Models/Space_Fighter.dae");
	Collision* collision = new Collision();
	addComponent(collision);
	this->loadLaser();
}

void EnemyFighter::chase(vector3df target)
{
	Enemy::chase(target);
}

void EnemyFighter::loadLaser()
{
	this->_nrLasers = 5;
	for (int i = 0; i< _nrLasers; i++)
	{
		this->_laser.push_back(new Laser);
	}
	this->_curLaser = 0;
	this->_fireTime = 0;

	for (int i = 0; i < this->_nrLasers; i++)
	{
		this->scene->addChild(this->_laser[i]);
	}
}

void EnemyFighter::update()
{
	EnemyFighter::stateSwitch->updateState();
	EnemyFighter::inRangeList.clear();

	if(EnemyFighter::stateSwitch->getState() == StateSwitch::STATE_OFFENSIVE)
	{
		//Should be activated when in current state
		this->_fireTime++;

		if(this->_fireTime >= 400)
		{
			//fire laser to target
			this->fireLaserAt(this->getTarget());
			this->_fireTime = 0;
		}
		this->_laser[this->_curLaser]->update();
	}

	Enemy::update();
}

EnemyFighter::~EnemyFighter(void)
{
	delete EnemyFighter::stateSwitch;

	Entity::~Entity();
}

void EnemyFighter::fireLaserAt(vector3df target)
{
	this->_laser[this->_curLaser]->fire(this, target, 1.0f);
	this->_curLaser++;
	
	if(this->_curLaser >= 5)
	{
		this->_curLaser = 0;
	}
}

vector<Laser*> EnemyFighter::GetLasers()
{
	return _laser;
}

