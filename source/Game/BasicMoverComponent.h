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

	BasicMoverComponent(GameObject* parent);
	virtual ~BasicMoverComponent();
	virtual void update();
protected:
	GameObject* _parent;

	void move(irr::core::vector3df vel);
	void rotate(irr::core::vector3df rot);
	void turn(irr::f32 rot);
	void pitch(irr::f32 rot);
	void roll(irr::f32 rot);
};

#endif