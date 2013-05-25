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




void BasicMoverComponent::move(Entity *entity, irr::core::vector3df vel)
{
	irr::core::matrix4 m;
	m.setRotationDegrees(*entity->transform->rotation);
	m.transformVect(vel);
	entity->transform->position->set(*entity->transform->position + vel);
	entity->transform->position;

}

void BasicMoverComponent::rotate(Entity *entity, irr::core::vector3df rot)
{
	irr::core::matrix4 m;
	m.setRotationDegrees(*entity->transform->rotation);
	irr::core::matrix4 n;
	n.setRotationDegrees(rot);
	m *= n;
	entity->transform->rotation->set(m.getRotationDegrees());
}

void BasicMoverComponent::turn(Entity *entity, irr::f32 rot)
{
	rotate(entity, irr::core::vector3df(0.0f, rot, 0.0f));
}

void BasicMoverComponent::pitch(Entity *entity, irr::f32 rot)
{
	rotate(entity, irr::core::vector3df(rot, 0.0f, 0.0f));
}

void BasicMoverComponent::roll(Entity *entity, irr::f32 rot)
{
	rotate(entity, irr::core::vector3df(0.0f, 0.0f, rot));
}