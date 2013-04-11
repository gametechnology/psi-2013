#include <Engine\CameraMover.h>


CameraMover::CameraMover(Camera* parent):Component(parent)
{
	cam = (Camera*)(parent);
	
}

void CameraMover::update()
{
	cam->position = cam->node->getPosition();
	cam->orientation = cam->node->getRotation();
	if (cam->parentIsEntity)
	{
		cam->position -= oldParentPosition;
		cam->orientation -= oldParentOrientation;
		cam->position += cam->getEntity()->position;
		cam->orientation += cam->getEntity()->orientation;
	}
	oldParentPosition = cam->getEntity()->position;
	oldParentOrientation = cam->getEntity()->orientation;


	vector3df tempPosition = cam->position;
	vector3df tempRotation = cam->orientation;

	vector3df forward = vector3df(0,0,1);
	vector3df right = vector3df(1,0,0);
	vector3df up = vector3df(0,1,0);
	matrix4 nodeRotation = matrix4().setRotationDegrees(tempRotation);
	
	nodeRotation.transformVect(forward);
	nodeRotation.transformVect(right);
	nodeRotation.transformVect(up);

	cam->getCameraNode()->setTarget(cam->position + forward);
	cam->getCameraNode()->setUpVector(cam->position +up);
}

CameraMover::~CameraMover()
{
}
