#ifndef CAMERAMOVER
#define CAMERAMOVER

#include "Engine/Component.h"
#include "Engine/Camera.h"

class CameraMover :	public Component
{
public:
	CameraMover();
	virtual ~CameraMover();

	virtual void init();
	virtual void update();

	virtual void draw(){};
	virtual void handleMessage(unsigned int message) {};
private:
	Camera* camera;
};

#endif
