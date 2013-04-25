#include <Engine\CameraMover.h>


CameraMover::CameraMover() : Component() {
	
}

void CameraMover::init() {
	camera = (Camera*)(Component::entity);
}

void CameraMover::lateUpdate() {
	vector3df tempPosition = *camera->transform->position;
	vector3df tempRotation = *camera->transform->rotation;

	vector3df forward = vector3df(0,0,1);
	vector3df right = vector3df(1,0,0);
	vector3df up = vector3df(0,1,0);
	matrix4 nodeRotation = matrix4().setRotationDegrees(tempRotation);
	
	nodeRotation.transformVect(forward);
	nodeRotation.transformVect(right);
	nodeRotation.transformVect(up);

	camera->setTarget(*camera->transform->position + forward);
	camera->setUpVector(*camera->transform->position + up);
}

CameraMover::~CameraMover() {

}
