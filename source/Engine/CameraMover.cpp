#include <Engine\CameraMover.h>


CameraMover::CameraMover() : Component() {
	
}

void CameraMover::init() {
	camera = (Camera*)(Component::entity);
}

void CameraMover::update() {
	irr::core::vector3df offset = irr::core::vector3df(0);

	irr::core::matrix4 m;
	m.setRotationDegrees(camera->parent->transform->rotation);

	irr::core::vector3df frv = irr::core::vector3df (0.0f, 0.0f, 1.0f);
	m.transformVect(frv);

	irr::core::vector3df upv = irr::core::vector3df (0.0f, 1.0f, 0.0f);
	m.transformVect(upv);

	m.transformVect(offset);

	offset += camera->parent->transform->position;
	camera->getCameraNode()->setPosition(offset);

	camera->getCameraNode()->setUpVector(upv);

	offset += frv;
	camera->getCameraNode()->setTarget(offset);

	camera->getCameraNode()->updateAbsolutePosition();
}

CameraMover::~CameraMover() {

}
