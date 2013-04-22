#include "Engine\Transform.h"

Transform::Transform() : Component() {

}
void Transform::update(){
	*velocity += *acceleration;
	*position += *velocity;
}
Transform::~Transform() {

}