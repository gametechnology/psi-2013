#include "Laser.h"
#include "Engine\IrrlichtNode.h"

Laser::Laser() : Entity()
{
	this->_currentLife = 0;
	this->_timeofLife = 100;
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