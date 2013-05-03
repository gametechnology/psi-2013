#include "Laser.h"
#include "Engine\IrrlichtNode.h"

Laser::Laser() : Entity()
{
	this->_currentLife = 0;
	this->_timeofLife = 100;
	this->_damage = 1;
}

void Laser::onAdd() {
	addChild(new IrrlichtNode(irr::io::path("../assets/Models/laser.3ds")));
}

void Laser::init() {
	disable();
}

Laser::~Laser() {
	Entity::~Entity();
}

void Laser::fire(Entity* origin, vector3df target, f32 speed)
{
	Composite::enable();
	
	transform->position = origin->transform->position;
	transform->rotation = parent->transform->rotation;
	transform->rotation += 90;
	
	this->_direction = target - *transform->position;
	this->_direction.normalize();

	*transform->velocity = _direction * speed;
}

void Laser::update()
{
	if(this->isAlive)
	{
		this->_currentLife++;
		if(this->_currentLife >= this->_timeofLife)
		{
			transform->velocity = new vector3df(0,0,0);
			disable();

			_currentLife = 0;
		}
	}

	Entity::update();
}

void Laser::contactResolver(Enemy* input)
{
	input->setHealth(input->getHealth() - this->_damage);
	std::printf("HIT on Enemy!");
//	delete(this); //'kill' this projectile
}

void Laser::contactResolver(DefenceStation* input)
{
	input->Damage();
	std::printf("HIT on Defence station!");
//	delete(this); //'kill' this projectile
}