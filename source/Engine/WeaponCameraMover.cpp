#include <Engine\WeaponCameraMover.h>
#include <Engine\InputManager.h>

WeaponCameraMover::WeaponCameraMover() : Component() {
}

void WeaponCameraMover::init() {
	weaponCamera = (WeaponCamera*)(Component::entity);
	yawChange = 0;
	rollChange = 0;
	pitchChange = 0;
	/*input = new InputManager*;*/
}

void WeaponCameraMover::update() {
	irr::core::vector3df offset = irr::core::vector3df(0);

	irr::core::matrix4 m;
	m.setRotationDegrees(*weaponCamera->parent->transform->rotation);

	irr::core::vector3df frv = irr::core::vector3df (0.0f, 0.0f, 1.0f);
	m.transformVect(frv);

	irr::core::vector3df upv = irr::core::vector3df (0.0f, 1.0f, 0.0f);
	m.transformVect(upv);

	m.transformVect(offset);

		//Transform naar aanleiding van knoppen
	/*
	if(input->isKeyBoardButtonDown(KEY_KEY_W)){
	}
	if(input->isKeyBoardButtonDown(KEY_KEY_A)){
	
	}
	if(input->isKeyBoardButtonDown(KEY_KEY_S)){
	
	}
	if(input->isKeyBoardButtonDown(KEY_KEY_D)){
	
	}*/

	offset += *weaponCamera->parent->transform->position;
	weaponCamera->getCameraNode()->setPosition(offset);

	weaponCamera->getCameraNode()->setUpVector(upv);

	offset += frv;
	weaponCamera->getCameraNode()->setTarget(offset);

	weaponCamera->getCameraNode()->updateAbsolutePosition();
}

WeaponCameraMover::~WeaponCameraMover(void)
{
}