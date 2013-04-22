#include "Engine\Transform.h"

Transform::Transform() : Component() {
  mass = 1;
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