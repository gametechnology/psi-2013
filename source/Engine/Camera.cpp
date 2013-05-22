#include <Engine\Camera.h>
#include <Engine\Game.h>
#include <Engine\CameraMover.h>

Camera::Camera() : IrrlichtNode("") {
}

void Camera::onAdd() {
	addComponent(new CameraMover());
}
void Camera::createNode() {
	irr::core::vector3df lookAt = *this->transform->position + irr::core::vector3df(0,0,-100); 
	this->cameraNode = this->scene->getIrrlichtSceneManager()->addCameraSceneNode(NULL, *this->transform->position, lookAt);
}
irr::scene::ICameraSceneNode* Camera::getCameraNode() {
	return ((irr::scene::ICameraSceneNode*)(cameraNode));
}

void Camera::setTarget(irr::core::vector3df target) {
	cameraNode->setTarget(target);
}

void Camera::setUpVector(irr::core::vector3df up) {
	cameraNode->setUpVector(up);
}

Camera::~Camera()
{
	cameraNode->remove();
	IrrlichtNode::~IrrlichtNode();
}
