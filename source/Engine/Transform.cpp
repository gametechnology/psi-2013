#include "Engine\Transform.h"

Transform::Transform() : Component() {
	mass = 1;

	position = irr::core::vector3df();
	rotation = irr::core::vector3df();
	velocity = irr::core::vector3df();
	acceleration = irr::core::vector3df();
	angularVelocity = irr::core::vector3df();
	angularAccelaration = irr::core::vector3df();
	radii = irr::core::vector3df(1,1,1);
}

void Transform::init() {
	Component::init();
}

void Transform::update() {
	angularVelocity += angularAccelaration;
	rotation += angularVelocity;

	acceleration = (1 / this->mass) * this->force;
	velocity += acceleration;
	position += velocity;

	Component::update();
}

Transform::~Transform() {

}