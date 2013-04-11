#include "EnemyPlayer.h"
#include "Engine/Entity.h"
#include <iostream>

EnemyPlayer::EnemyPlayer(irr::core::vector3df position, vector3df speed): Enemy()
{
	this->setVisualWithPath("../assets/Models/player.dae");
	this->setPosition(position);
	this->setMaxHealth(100);
	this->setAgility(1);
	this->setMaxSpeed(400);	
	this->setAccelaration(vector3df(0,0,0));	
	this->setRadius(1);
	this->setVelocity(speed);
}

EnemyPlayer::~EnemyPlayer(void)
{

}
