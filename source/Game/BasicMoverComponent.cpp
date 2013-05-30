#include "BasicMoverComponent.h"

using namespace irr;
using namespace irr::core;

BasicMoverComponent::BasicMoverComponent(GameObject* parent) : Component("BasicMoverComponent")
{
	_parent = parent;
	thrust = 0;	
}

BasicMoverComponent::~BasicMoverComponent()
{

}

void BasicMoverComponent::update()
{
	vector3df direction = _parent->getRotation()->rotationToDirection();
	_parent->setVelocity(&(direction * thrust));
}

void BasicMoverComponent::move(vector3df vel)
{
	matrix4 m;
	m.setRotationDegrees(*_parent->getRotation());
	m.transformVect(vel);
	_parent->setVelocity(&vel);
}

void BasicMoverComponent::rotate(vector3df rot)
{
	matrix4 m;
	m.setRotationDegrees(*_parent->getRotation());
	matrix4 n;
	n.setRotationDegrees(rot);
	m *= n;
	_parent->setRotation(m.getRotationDegrees());
}

void BasicMoverComponent::turn(f32 rot)
{
	rotate(vector3df(0.0f, rot, 0.0f));
}

void BasicMoverComponent::pitch(f32 rot)
{
	rotate(vector3df(rot, 0.0f, 0.0f));
}

void BasicMoverComponent::roll(f32 rot)
{
	rotate(vector3df(0.0f, 0.0f, rot));
}