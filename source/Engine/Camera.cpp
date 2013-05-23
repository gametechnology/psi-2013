#include <Engine\Camera.h>
#include <Engine\Game.h>
#include <Engine\CameraMover.h>

Camera::Camera() : IrrlichtNode("") {
	addComponent(new CameraMover());
}

void Camera::init() {
	Entity::init();

	createNode();
}

void Camera::createNode() {
	irr::core::vector3df lookAt = *this->parent->transform->position + irr::core::vector3df(0,0,-1); 
	this->node = this->scene->getIrrlichtSceneManager()->addCameraSceneNode(NULL, *this->parent->transform->position, lookAt);
	getCameraNode()->bindTargetAndRotation(true);
}

void Camera::update() {
	Entity::update();
}

irr::scene::ICameraSceneNode* Camera::getCameraNode() {
	return ((irr::scene::ICameraSceneNode*)(node));
}

void Camera::setTarget(irr::core::vector3df target) {
	getCameraNode()->setTarget(target);
}

void Camera::setUpVector(irr::core::vector3df up) {
	getCameraNode()->setUpVector(up);
}
