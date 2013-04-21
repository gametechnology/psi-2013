#include "BasicMoverComponent.h"

BasicMoverComponent::BasicMoverComponent(Entity* parent):Component()
{
	entityParent = this->entity->parent;
	thrust = 0;
}

BasicMoverComponent::~BasicMoverComponent()
{
	
}

void BasicMoverComponent::update()
{
	irr::core::vector3df direction(cos(entityParent->transform->rotation->Y)*cos(entityParent->transform->rotation->X),
		sin(entityParent->transform->rotation->Y)*cos(entityParent->transform->rotation->X),
		sin(entityParent->transform->rotation->X));
	entityParent->transform->velocity->set(direction * thrust);

	//printf("position: %f, %f, %f\n", entityParent->position.X, entityParent->position.Y, entityParent->position.Z);
	//printf("forwardMovement: %f, %f, %f\n", direction.X * thrust, direction.Y * thrust, direction.Z * thrust);
}