#include "EnemyDrone.h"
#include "Engine/Entity.h"
#include "Engine/Collision.h"

EnemyDrone::EnemyDrone(irr::core::vector3df position):Enemy()
{
	this->setPosition(position);
	this->setMaxHealth(25);
	this->setAgility(3);
	this->setMaxSpeed(250);
	this->setRadius(1);
	this->setOriginalRadius(1);
	this->setOuterRadius(sqrt((this->getRadius()*this->getRadius())+(this->getRadius()*this->getRadius())));
	this->setAccelaration(vector3df(75,0,0));
	this->setLoS(200);
	this->_type = Enemy::DRONE;
	
}

void EnemyDrone::init()
{
	Enemy::init();

	EnemyDrone::inRangeList = vector<Entity*>();
	EnemyDrone::stateSwitch = new StateSwitchDrone(StateSwitchDrone::States::STATE_WANDER, this);
}

void EnemyDrone::onAdd()
{
	Enemy::onAdd();

	this->setVisualWithPath("../assets/Models/Space_Drone.dae");

	Collision* collision = new Collision();
	addComponent(collision);
}

EnemyDrone::~EnemyDrone(void)
{
	EnemyDrone::stateSwitch->~StateSwitchDrone();
}

void EnemyDrone::chase(vector3df target)
{
	Enemy::chase(target);
}
void EnemyDrone::wander()
{
	Enemy::wander();
}
void EnemyDrone::update()
{
	EnemyDrone::stateSwitch->update();
	EnemyDrone::inRangeList.clear();
	Enemy::update();
}