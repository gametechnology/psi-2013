#include "Engine\Transform.h"

Transform::Transform() : Component() {
	mass = 1;

	position = new irr::core::vector3df();
	rotation = new irr::core::vector3df();
	velocity = new irr::core::vector3df();
	acceleration = new irr::core::vector3df();
	angularVelocity = new irr::core::vector3df();
	angularAccelaration = new irr::core::vector3df();
}

void Transform::init() {
	
}

void Transform::update(){
	*angularVelocity += *angularAccelaration;
	*rotation += *angularVelocity;

	*acceleration = (1 / this->mass) * this->force;
	*velocity += *acceleration;
	*position += *velocity;
}

Transform::~Transform() {

}