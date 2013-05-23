#include <Engine\WeaponCameraMover.h>
#include <Engine\InputManager.h>

WeaponCameraMover::WeaponCameraMover() : Component() {
}

void WeaponCameraMover::init() {
	weaponCamera = (WeaponCamera*)(Component::entity);
	input = new InputManager();
	irr::core::vector3df rotAngleVector = irr::core::vector3df (0.0f, 0.0f, 0.0f);
	XChange = 0;
	YChange = 0;
}

void WeaponCameraMover::update() {
	irr::core::vector3df offset = irr::core::vector3df(0);

	irr::core::matrix4 m;
	m.setRotationDegrees(*weaponCamera->parent->transform->rotation);

	irr::core::vector3df forwardVector = irr::core::vector3df (0.0f, 0.0f, 1.0f);
	m.transformVect(forwardVector);

	irr::core::vector3df upVector = irr::core::vector3df (0.0f, 1.0f, 0.0f);
	m.transformVect(upVector);

	irr::core::vector3df rightVector = irr::core::vector3df (1.0f, 0.0f, 0.0f);
	m.transformVect(rightVector);

	m.transformVect(offset);

	irr::core::matrix4 rotAngleButtons;
	
	//Transform naar aanleiding van knoppen
	if(input->isKeyboardButtonDown(KEY_KEY_W)){
		if(YChange <= 90){
			rotAngleVector.Y += 1;
			YChange += 1;
		}
	}
	if(input->isKeyboardButtonDown(KEY_KEY_S)){
		if(YChange >= -90){
			rotAngleVector.Y -= 1;
			YChange -= 1;
		}
	}
	if(input->isKeyboardButtonDown(KEY_KEY_A)){
		if(XChange >= -90){
			rotAngleVector.X -= 1;
			XChange -= 1;
		}
	}
	if(input->isKeyboardButtonDown(KEY_KEY_D)){
		if(XChange <= 90){
			rotAngleVector.X += 1;
			XChange += 1;
		}
	}

	rotAngleButtons.setRotationDegrees(rotAngleVector);
	rotAngleButtons.transformVect(upVector);


	offset += *weaponCamera->parent->transform->position;
	weaponCamera->getCameraNode()->setPosition(offset);

	weaponCamera->getCameraNode()->setUpVector(upVector);

	offset += forwardVector;
	weaponCamera->getCameraNode()->setTarget(offset);

	weaponCamera->getCameraNode()->updateAbsolutePosition();
}

WeaponCameraMover::~WeaponCameraMover(void)
{
}