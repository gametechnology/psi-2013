#include "EnemyPlayer.h"

using namespace irr;
using namespace irr::core;

EnemyPlayer::EnemyPlayer(irr::scene::ISceneManager* smgr, vector3df position, vector3df speed) : Enemy(smgr)
{
	setPosition(position);
	setMaxHealth(100);
	setAgility(1);
	setMaxSpeed(400);	
	setAcceleration(&vector3df(0,0,0));	
	setRadius(1);
	setOriginalRadius(1);
	setOuterRadius(1);
	setVelocity(&speed);
}

void EnemyPlayer::init()
{
	Enemy::init();
	setMesh("../assets/Models/Space_Fighter.dae");
}

EnemyPlayer::~EnemyPlayer()
{

}
