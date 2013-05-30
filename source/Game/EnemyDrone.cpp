#include "EnemyDrone.h"

using namespace irr;
using namespace irr::core;

EnemyDrone::EnemyDrone(irr::scene::ISceneManager* smgr, vector3df position) : Enemy(smgr)
{
	setPosition(position);
	setMaxHealth(25);
	setAgility(3);
	setMaxSpeed(250);
	setRadius(1);
	setOriginalRadius(1);
	setOuterRadius(sqrt((getRadius()->X * getRadius()->X) + (getRadius()->X * getRadius()->X)));
	setAcceleration(&vector3df(75,0,0));
	this->setLoS(200);
	this->_type = Enemy::DRONE;	
}

void EnemyDrone::init()
{
	Enemy::init();
	setMesh("../assets/Models/Space_Drone.dae");
	EnemyDrone::inRangeList = std::vector<GameObject*>();
	EnemyDrone::stateSwitch = new StateSwitchDrone(StateSwitchDrone::STATE_WANDER, this);
}

EnemyDrone::~EnemyDrone(void)
{
	delete this->stateSwitch;
	
	Enemy::~Enemy();
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