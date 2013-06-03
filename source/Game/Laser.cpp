#include "Laser.h"
#include "Engine\IrrlichtNode.h"
#include "EnemyDrone.h"
#include "EnemyAsteroid.h"
#include "EnemyFighter.h"
#include "DummyShip.h"

int Laser::newLaserId = 0;

Laser::Laser() : Enemy()
{	
	this->_currentLife = 0;
	this->_timeofLife = 250;
	this->_damage = 110;
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
		this->init();

		for(unsigned i = 0; i < this->children.size(); i++)
		{
			this->children[i]->update();
		}
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

void Laser::fire(Transform* transform, vector3df target, f32 speed)
{
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

void Laser::contactResolverA(Entity* input)
{
	Enemy* tempEnemy = dynamic_cast<Enemy*>(input);
	tempEnemy->setHealth(tempEnemy->getHealth() - this->_damage);
	 
	/*   if(dynamic_cast<DummyShip*>(input) != NULL)
	 {
	  std::printf("HIT on ship! \n");
	 }
	      if(dynamic_cast<EnemyFighter*>(input) != NULL)
	 {
	  std::printf("HIT on fighter! \n");
	 }
		     if(dynamic_cast<EnemyAsteroid*>(input) != NULL)
	 {
	  std::printf("HIT on asteroid! \n");
	 }
			    if(dynamic_cast<EnemyDrone*>(input) != NULL)
	 {
	  std::printf("HIT on drone! \n");
	 }*/

	std::printf("HIT on Enemy! \n");
	this->disable();
	for(unsigned i = 0; i < this->children.size(); i++)
	{
		this->children[i]->update();
	}	
	input->contactResolverA(this); //call the contactresolver from the other item as well
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
}