#ifndef BASICMOVERCOMPONENT
#define BASICMOVERCOMPONENT

#include <Engine/Component.h>
#include <Engine/GameObject.h>

#include "NetworkInterface.h"

class BasicMoverComponent : public Component   
{
public:
	float mass;
	float thrust;

	BasicMoverComponent();
	virtual ~BasicMoverComponent();
	virtual void update();
protected:
	void move(GameObject*, irr::core::vector3df vel);
	void rotate(GameObject*, irr::core::vector3df rot);
	void turn(GameObject*, irr::f32 rot);
	void pitch(GameObject*, irr::f32 rot);
	void roll(GameObject*, irr::f32 rot);
};

#endif