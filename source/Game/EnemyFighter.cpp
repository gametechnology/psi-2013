#include "EnemyFighter.h"
#include "Engine/Entity.h"

EnemyFighter::EnemyFighter(irr::core::vector3df position): Enemy()
{
	this->setVisualWithPath("../assets/Models/Space_Fighter.dae");
	this->setPosition(position);
	this->setHealth(50);
	this->setAgility(2);
	this->setMaxSpeed(400);
	this->setAccelaration(45);
	this->setLoS(4800);

	EnemyFighter::arrayList = ArrayList<Entity>();
	EnemyFighter::stateSwitch = new StateSwitchFighter(this);
}

void EnemyFighter::update()
{
	EnemyFighter::stateSwitch->updateState();
	Enemy::update();
}

EnemyFighter::~EnemyFighter(void)
{
	delete EnemyFighter::stateSwitch;
}

