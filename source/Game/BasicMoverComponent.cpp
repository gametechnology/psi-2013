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
	irr::core::vector3df direction = entity->transform->rotation->rotationToDirection();
	entity->transform->velocity->set(direction * thrust);
}