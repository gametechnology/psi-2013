#include <Engine\Camera.h>
#include <Engine\Game.h>
#include <Engine\CameraMover.h>

Camera::Camera() : IrrlichtNode("") {
	
}

void Camera::onAdd() {
	IrrlichtNode::onAdd();

	addComponent(mover = new CameraMover());
}

void Camera::handleMessage(unsigned int message) {
	switch (message)
	{
	case 0: // This is DAMAGE, if I'm not mistaken.
		shake();
		break;
	}
}

void Camera::init() {
	Entity::init();

	createNode();
}

void Camera::createNode() {
	irr::core::vector3df lookAt = this->parent->transform->position + irr::core::vector3df(0,0,-1); 
	this->node = this->scene->getIrrlichtSceneManager()->addCameraSceneNode(NULL, this->parent->transform->position, lookAt);
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

void Camera::shake() {
	mover->shake();
}
