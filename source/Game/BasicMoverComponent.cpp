#include "BasicMoverComponent.h"

BasicMoverComponent::BasicMoverComponent(Entity* parent):Component(parent)
{
	entityParent = parent;
	thrust = 0;
}

BasicMoverComponent::~BasicMoverComponent()
{
	
}

void BasicMoverComponent::update()
{
	vector3df direction = entityParent->orientation.rotationToDirection(vector3df(1,0,0));
	entityParent->velocity.set(direction * thrust);
	//printf("position: %f, %f, %f\n", entityParent->position.X, entityParent->position.Y, entityParent->position.Z);
	//printf("forwardMovement: %f, %f, %f\n", direction.X * thrust, direction.Y * thrust, direction.Z * thrust);
}