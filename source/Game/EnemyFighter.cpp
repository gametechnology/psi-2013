#include "EnemyFighter.h"
#include "StateSwitchFighter.h"

using namespace irr;
using namespace irr::core;

ObjectPool<Laser>* EnemyFighter::laserPool;

EnemyFighter::EnemyFighter(irr::scene::ISceneManager* smgr, irr::core::vector3df position) : Enemy(smgr)
{
	setPosition(position);
	setMaxHealth(50);
	setAgility(2);
	setMaxSpeed(400);
	setRadius(1);
	setOriginalRadius(1);
	setOuterRadius(1);
	setAcceleration(&vector3df(45,0,0));
	setLoS(4800);
	_type = Enemy::FIGHTER;

}

void EnemyFighter::init()
{
	inRangeList = std::vector<GameObject*>();
	stateSwitch = new StateSwitchFighter(StateSwitchFighter::STATE_WANDER,this);

	setMesh("../assets/Models/Space_Fighter.dae");
	this->_fireTime = 0;

	Enemy::init();
}

void EnemyFighter::chase(vector3df target)
{
	Enemy::chase(target);
}

void EnemyFighter::update()
{
	stateSwitch->update();

	// Ugly hack. 
	/*if(game->input->isKeyboardButtonPressed(irr::KEY_KEY_M))
	{
	this->fireLaserAt(vector3df(200));
	}*/

	inRangeList.clear();

	Enemy::update();
}

EnemyFighter::~EnemyFighter(void)
{
	GameObject::~GameObject();
}

void EnemyFighter::fireLaserAt(vector3df target)
{
	Laser* laser = this->laserPool->GetFreeObject();
	if(laser != NULL)
	{
		laser->fire(_position, _rotation, target, 1.0f);
	}
}

