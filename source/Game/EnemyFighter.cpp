#include "EnemyFighter.h"
#include "Engine/Entity.h"
#include "Engine/Collision.h"

ObjectPool<Laser> EnemyFighter::laserPool;

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
	EnemyFighter::stateSwitch = new StateSwitchFighter(StateSwitch::STATE_WANDER,this);
}

void EnemyFighter::onAdd() 
{
	Enemy::onAdd();
	this->setVisualWithPath("../assets/Models/Space_Fighter.dae");
	Collision* collision = new Collision();
	addComponent(collision);

	this->_fireTime = 0;
}

void EnemyFighter::chase(vector3df target)
{
	Enemy::chase(target);
}

void EnemyFighter::update()
{
	EnemyFighter::stateSwitch->updateState();

	if(game->input->isKeyboardButtonPressed(irr::KEY_KEY_M))
	{
		this->fireLaserAt(vector3df(this->getTarget().X , this->getTarget().Y , this->getTarget().Z ));
	}

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
	}

	EnemyFighter::inRangeList.clear();

	Enemy::update();
}

EnemyFighter::~EnemyFighter(void)
{
	delete EnemyFighter::stateSwitch;

	Entity::~Entity();
}

void EnemyFighter::fireLaserAt(vector3df target)
{
	Laser* laser = this->laserPool.GetFreeObject();
	if(laser != NULL)
	{
		laser->fire(this->scene, this->transform, target, 1.0f);
	}
}

void EnemyFighter::contactResolverA(Entity* input)
{
	std::printf("HIT on Fighter!");
	Entity::contactResolverA(input);
}


