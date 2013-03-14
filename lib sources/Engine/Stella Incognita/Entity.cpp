#include "Entity.h"

Entity::Entity()
{
	Composite::Composite();

	this->mass = 1;
}

Entity::Entity(Composite* parent):Composite(parent)
{
	this->mass = 1;
}

void Entity::update()
{
	Composite::update();

	//this->angularAccelaration = ();
	this->angularVelocity += this->angularAccelaration;
	this->orientation += this->angularVelocity;

	this->accelaration = (1 / this->mass) * this->force;
	this->velocity += this->accelaration;
	this->position += this->velocity;

	//this->irrNode->setPosition(this->position);
	//this->irrNode->setRotation(this->orientation);
}

void Entity::draw()
{
	if (!this->visible)
	{
		this->irrNode->setVisible(false);
		return;
	}
	this->irrNode->setVisible(true);

	this->irrNode->render();
}

Entity::~Entity()
{
	delete irrNode;
}