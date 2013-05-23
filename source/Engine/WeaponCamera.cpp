#include "WeaponCamera.h"
#include <Engine\Game.h>
#include "WeaponCameraMover.h"


WeaponCamera::WeaponCamera() : IrrlichtNode("") {
	addComponent(new WeaponCameraMover());
}

WeaponCamera::~WeaponCamera(void)
{
}

void WeaponCamera::init() {
	Entity::init();

	createNode();
}

void WeaponCamera::createNode() {
	irr::core::vector3df lookAt = *this->parent->transform->position + irr::core::vector3df(0,0,-1); 
	this->node = this->scene->getIrrlichtSceneManager()->addCameraSceneNode(NULL, *this->parent->transform->position, lookAt);
	getCameraNode()->bindTargetAndRotation(true);
}

void WeaponCamera::update() {
	Entity::update();
}

irr::scene::ICameraSceneNode* WeaponCamera::getCameraNode() {
	return ((irr::scene::ICameraSceneNode*)(node));
}

void WeaponCamera::setTarget(irr::core::vector3df target) {
	getCameraNode()->setTarget(target);
}

void WeaponCamera::setUpVector(irr::core::vector3df up) {
	getCameraNode()->setUpVector(up);
}
