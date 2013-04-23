#include "BasicMoverComponent.h"

BasicMoverComponent::BasicMoverComponent() : Component()
{
	thrust = 0;
}

BasicMoverComponent::~BasicMoverComponent()
{
	
}

void BasicMoverComponent::update()
{
	irr::core::vector3df direction(cos(entity->transform->rotation->Y)*cos(entity->transform->rotation->X),
		sin(entity->transform->rotation->Y)*cos(entity->transform->rotation->X),
		sin(entity->transform->rotation->X));
	entity->transform->velocity->set(direction * thrust);

	//printf("position: %f, %f, %f\n", entityParent->position.X, entityParent->position.Y, entityParent->position.Z);
	//printf("forwardMovement: %f, %f, %f\n", direction.X * thrust, direction.Y * thrust, direction.Z * thrust);
}