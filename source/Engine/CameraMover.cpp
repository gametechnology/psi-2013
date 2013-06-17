#include <Engine\CameraMover.h>
#include <Engine\Game.h>

CameraMover::CameraMover() : Component() {
	
}

void CameraMover::init() {
	camera = (Camera*)(Component::entity);

	shakeStrength = 0;
	shakeDecrease = 0.1f;
}

void CameraMover::update() {
	irr::core::vector3df offset = irr::core::vector3df(0);

	irr::core::matrix4 m;
	m.setRotationDegrees(camera->parent->transform->rotation);

	irr::core::vector3df frv = irr::core::vector3df (0.0f, 0.0f, 1.0f);
	m.transformVect(frv);

	irr::core::vector3df upv = irr::core::vector3df (0.0f, 1.0f, 0.0f);
	m.transformVect(upv);

	irr::core::vector3df riv = irr::core::vector3df (1.0f, 0.0f, 0.0f);
	m.transformVect(riv);

	m.transformVect(offset);

	if (shakeStrength > shakeDecrease)
		shakeStrength -= shakeDecrease;
	else
		shakeStrength = 0;

	if (this->getGame()->input->isKeyboardButtonReleased(KEY_KEY_H)) {
		shake();
	}

	offset += camera->parent->transform->position;
	offset += riv * (((rand()%2) > 0) ? -1.0f : 1.0f) * shakeStrength;
	offset += upv * (((rand()%2) > 0) ? -1.0f : 1.0f) * shakeStrength;
	camera->getCameraNode()->setPosition(offset);

	camera->getCameraNode()->setUpVector(upv);

	offset += frv;
	camera->getCameraNode()->setTarget(offset);

	camera->getCameraNode()->updateAbsolutePosition();
}

void CameraMover::shake() {
	shakeStrength = 3.0f;
}

CameraMover::~CameraMover() {

}