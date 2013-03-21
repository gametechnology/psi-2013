#include "Engine\CameraMover.h"


CameraMover::CameraMover(Camera* parent):Component(parent)
{

}

void CameraMover::update()
{
	Camera* cam = (Camera*)(parent);
	cam->position = cam->node->getPosition();
	cam->orientation = cam->node->getRotation();
	if (cam->parentIsEntity)
	{
		cam->position -= oldParentPosition;
		cam->orientation -= oldParentOrientation;
		cam->position += cam->getEntity()->position;
		cam->orientation += cam->getEntity()->orientation;
	}
}

CameraMover::~CameraMover()
{
}
