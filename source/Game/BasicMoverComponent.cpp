#include "BasicMoverComponent.h"

BasicMoverComponent::BasicMoverComponent(Entity* parent):Component(parent)
{
	entityParent = parent;
	thrust = 0.1f;
}

BasicMoverComponent::~BasicMoverComponent()
{
	
}

void BasicMoverComponent::update()
{
	vector3df forwardMovement(cos(entityParent->orientation.Y)*cos(entityParent->orientation.X),
		sin(entityParent->orientation.Y)*cos(entityParent->orientation.X),
		sin(entityParent->orientation.X));
	forwardMovement *= thrust;
	entityParent->velocity.set(forwardMovement);

	printf("position: %f, %f, %f\n", entityParent->position.X, entityParent->position.Y, entityParent->position.Z);
	printf("forwardMovement: %f, %f, %f\n", forwardMovement.X, forwardMovement.Y, forwardMovement.Z);
}