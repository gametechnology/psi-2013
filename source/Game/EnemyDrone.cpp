#include "EnemyDrone.h"
#include "Engine/Entity.h"

EnemyDrone::EnemyDrone(irr::core::vector3df position):Enemy()
{
	this->setVisualWithPath("../assets/Models/Space_Drone.dae");
	this->setPosition(position);
	this->setMaxHealth(25);
	this->setAgility(3);
	this->setMaxSpeed(250);
	this->setAccelaration(vector3df(75,0,0));
	this->setLoS(200);

	EnemyDrone::inRangeList = array<Entity*>();
	EnemyDrone::stateSwitch = new StateSwitchDrone(StateSwitch::STATE_WANDER, this);
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
	EnemyDrone::stateSwitch->updateState();
	EnemyDrone::inRangeList.clear();
	Enemy::update();
}