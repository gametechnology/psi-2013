#include "Laser.h"
#include "Engine\IrrlichtNode.h"
#include "NetworkInterface.h"

int Laser::newLaserId = 0;

Laser::Laser() : Entity()
{
	this->_currentLife = 0;
	this->_timeofLife = 250;
	this->_damage = 1;
	this->disable();
	this->scene = NULL;
	this->_hasAnIrrlichtNode = false;
	this->_id = this->newLaserId++;

	//the addchild is located in the constructor because a laser is being added more than once
}

void Laser::onAdd() {
	if(!this->_hasAnIrrlichtNode)
	{
		addChild(new IrrlichtNode("../assets/Models/laser.3ds"));
		this->_hasAnIrrlichtNode = true;
	}
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
	*this->transform->rotation += 90;
	
	this->_direction = target - *this->transform->position;
	this->_direction.normalize();

	*this->transform->velocity = _direction * speed;
}

int Laser::getId()
{
	return this->_id;
}

void Laser::setId(int id)
{
	this->_id = id;
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

void Laser::contactResolverA(Enemy* input)
{
	input->setHealth(input->getHealth() - this->_damage);
	std::printf("HIT on Enemy!");
	this->disable();
//	delete(this); //'kill' this projectile
}

void Laser::contactResolverA(DefenceStation* input)
{
	input->Damage();
	std::printf("HIT on Defence station!");
	this->disable();
//	delete(this); //'kill' this projectile
}