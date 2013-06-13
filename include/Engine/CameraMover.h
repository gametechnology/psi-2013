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
	virtual void handleMessage(unsigned int message){};

	void shake();
private:
	Camera* camera;

	irr::f32 shakeStrength;
	irr::f32 shakeDecrease;
};

#endif
