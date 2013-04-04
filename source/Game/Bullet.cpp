#include "Bullet.h"
#include "Ship.h"
Bullet::Bullet() : Entity(NULL)
{
	this->visible = false;

	this->createNode("../../assets/Models/Cube.3ds");
	this->node->setMaterialFlag(EMF_LIGHTING, false);
}

Bullet::Bullet(Composite* parent, vector3df start, vector3df end, f32 speed) : Entity(parent)
{
	this->createNode("../../assets/Models/Cube.3ds");
	this->node->setMaterialFlag(EMF_LIGHTING, false);

	setState(NULL, start, end, speed);
}

Bullet::~Bullet()
{
	Entity::~Entity();
}

void Bullet::update()
{
	Entity::update();

	this->_currentFlightTime++;
	
	if(this->visible && this->_currentFlightTime > this->_maxFlightTime &&  ((Ship*)&parent)->stationnumber == 1)
	{
		this->visible = false;
		this->velocity = vector3df(0, 0, 0);
	}
}

void Bullet::setState(Composite* parent, vector3df start, vector3df end, f32 speed)
{
	if(parent != NULL)
	{
		this->parent = parent;
	}
	this->visible = true;

	end.normalize();
	start += end*8.0f;
	end = start + (end * Game::device->getSceneManager()->getActiveCamera()->getFarValue());

	vector3df direction = (end - start).normalize();

	this->position = start;
	this->velocity = direction*(speed/10);
	this->angularVelocity = vector3df(0.1, 0.1, 0.1);

	f32 length = (f32)(end - start).getLength();
	this->_maxFlightTime = (u32)(length / speed);
	this->_currentFlightTime = 0;
}