#include <Engine\Camera.h>
#include <Engine\Game.h>
#include <Engine\CameraMover.h>


Camera::Camera() : IrrlichtNode("") {
}

void Camera::onAdd() {
	addComponent(new CameraMover());
}
void Camera::createNode() {
	irr::core::vector3df lookAt = *this->transform->position + irr::core::vector3df(0,0,1); 
	this->node = this->scene->getIrrlichtSceneManager()->addCameraSceneNode(NULL, *this->transform->position, lookAt);
}
irr::scene::ICameraSceneNode* Camera::getCameraNode() {
	return ((irr::scene::ICameraSceneNode*)(node));
}

void Camera::setTarget(irr::core::vector3df target) {
	node->setTarget(target);
}

void Camera::setUpVector(irr::core::vector3df up) {
	node->setUpVector(up);
}

Camera::~Camera()
{
	IrrlichtNode::~IrrlichtNode();
}
