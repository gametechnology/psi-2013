#include <Engine\Camera.h>
#include <Engine\Game.h>
#include <Engine\CameraMover.h>


Camera::Camera() : IrrlichtNode("") {
}

void Camera::onAdd() {
	this->node = this->entity->scene->getIrrlichtSceneManager()->addCameraSceneNode(NULL, position, lookAt);
	entity->addComponent(new CameraMover());
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
	Entity::~Entity();
}
