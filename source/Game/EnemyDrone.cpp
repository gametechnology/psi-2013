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
	this->setLoS(2000);
	EnemyDrone::arrayList = ArrayList<Entity>();
	EnemyDrone::stateSwitch = new StateSwitchDrone(StateSwitch::STATE_WANDER, this);
}
EnemyDrone::~EnemyDrone(void)
{
	EnemyDrone::stateSwitch->~StateSwitchDrone();
}

void EnemyDrone::update()
{
	EnemyDrone::stateSwitch->updateState();
	Enemy::update();
}