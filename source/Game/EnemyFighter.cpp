#include "EnemyFighter.h"
#include "Engine/Entity.h"
#include "Engine/Collision.h"

ObjectPool<Laser>* EnemyFighter::laserPool;

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

	inRangeList = vector<Entity*>();
	stateSwitch = new StateSwitchFighter(StateSwitchFighter::States::STATE_WANDER,this);
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
	EnemyFighter::stateSwitch->update();

	if(game->input->isKeyboardButtonPressed(irr::KEY_KEY_M))
	{
		std::cout<<"schiet"<<endl;
		//this->_fireTime++;

		//if(this->_fireTime >= 100)
		//{
			//fire laser to target
			this->fireLaserAt(this->getTarget());
			std::cout<<"target " << (this->getTarget().X)<<endl;
			//this->_fireTime = 0;
		//}
	}

	/*if(EnemyFighter::stateSwitch->getState() == STATE_OFFENSIVE)
	{
		//Should be activated when in current state
		this->_fireTime++;

		if(this->_fireTime >= 200)
		{
			//fire laser to target
			this->fireLaserAt(this->getTarget());
			this->_fireTime = 0;
		}
	}*/

	EnemyFighter::inRangeList.clear();

	Enemy::update();
}

EnemyFighter::~EnemyFighter(void)
{
	delete stateSwitch;

	Enemy::~Enemy();
}

void EnemyFighter::fireLaserAt(vector3df target)
{
	Laser* laser = this->laserPool->GetFreeObject();
	if(laser != NULL)
	{
		laser->fire(this->transform, target, 1.0f);
	}
}

void EnemyFighter::contactResolverA(Entity* input)
{
	std::printf("HIT on Fighter! \n");
	Entity::contactResolverA(input);
}


