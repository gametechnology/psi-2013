#include "Laser.h"
#include "Engine\IrrlichtNode.h"
#include "EnemyDrone.h"

Laser::Laser() : Enemy()
{	
	this->_currentLife = 0;
	this->_timeofLife = 250;
	this->_damage = 10;
	this->disable();
	this->scene = NULL;
	this->_hasAnIrrlichtNode = false;

	//the addchild is located in the constructor because a laser is being added more than once
}

void Laser::onAdd() {
	if(!this->_hasAnIrrlichtNode)
	{
		addChild(new IrrlichtNode("../assets/Models/laser.3ds"));
		this->_hasAnIrrlichtNode = true;
	}
	Collision *coll = new Collision();
	this->addComponent(coll);
	Entity::onAdd();
}

void Laser::init() {
	Entity::init();
}

Laser::~Laser() 
{

}

void Laser::fire(Scene* scene, Transform* transform, vector3df target, f32 speed)
{
	if(this->scene != NULL)
	{
		this->scene->removeChild(this, false);
	}

	this->scene = scene;
	this->scene->addChild(this);
	this->enable();

	*this->transform->position = *transform->position;
	*this->transform->rotation = *transform->rotation;
	
	this->_direction = target - *this->transform->position;
	this->_direction.normalize();
	this->transform->position->dotProduct(this->_direction);
	this->transform->position->operator+=(this->_direction);
	this->transform->position->operator+=(this->_direction);
	this->transform->position->operator+=(this->_direction);
	this->transform->position->operator+=(this->_direction);
	*this->transform->rotation = this->_direction;

	//*this->transform->rotation += 90;

	*this->transform->velocity = this->_direction * speed;
}

void Laser::update()
{
	if(this->enabled)
	{
		this->_currentLife++;
		if(this->_currentLife >= this->_timeofLife)
		{
			this->disable();
			for(unsigned i = 0; i < this->children.size(); i++)
			{
				this->children[i]->update();
			}
			_currentLife = 0;
		}
	}

	Entity::update();
}

void Laser::contactResolverA(Entity* input)
{
	Enemy* tempEnemy = dynamic_cast<Enemy*>(input);
	tempEnemy->setHealth(tempEnemy->getHealth() - this->_damage);
	//if(tempEnemy->getType()==tempEnemy->ASTROID)
	//{
	//	std::printf("HIT on ASTROID!");
	//}
	//if(tempEnemy->getType()==tempEnemy->DRONE)
	//{
	//	std::printf("HIT on DRONE!");
	//}
	//if(tempEnemy->getType()==tempEnemy->FIGHTER)
	//{
	//	std::printf("HIT on FIGHTER!");
	//}
	//input->setHealth(input->getHealth() - this->_damage);
	std::printf("HIT on Enemy! \n");
	this->disable();
	for(unsigned i = 0; i < this->children.size(); i++)
	{
		this->children[i]->update();
	}
//	delete(this); //'kill' this projectile
}

void Laser::contactResolverA(DefenceStation* input)
{
	input->Damage();
	std::printf("HIT on Defence station! \n");
	this->disable();
	for(unsigned i = 0; i < this->children.size(); i++)
	{
		this->children[i]->update();
	}
//	delete(this); //'kill' this projectile
}