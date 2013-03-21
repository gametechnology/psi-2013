#include "Component.h"
#include "Camera.h"

#ifndef CAMERAMOVER
#define CAMERAMOVER

class CameraMover :	public Component
{
public:
	CameraMover(Camera* parent);
	virtual ~CameraMover();
	virtual void update();
	virtual void handleMessage(unsigned int message, void* data) {};
private:
	vector3df oldParentPosition;
	vector3df oldParentOrientation;
};

#endif
