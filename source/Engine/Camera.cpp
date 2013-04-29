#include <Engine\Camera.h>
#include <Engine\Game.h>
#include <Engine\CameraMover.h>


Camera::Camera() : IrrlichtNode("") {
}

void Camera::onAdd() {
	entity->addComponent(new CameraMover());
}
void Camera::createNode() {
	printf("[Camera]-CreateNode \n");
	//this->node = this->entity->scene->getIrrlichtSceneManager()->addCameraSceneNode(NULL, position, lookAt);
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
