#ifndef TRANSFORM
#define TRANSFORM

#include "Engine\Component.h"

class Transform : public Component {
public:
	float mass;
	vector3d<float> force;
	vector3d<float> position;
	vector3d<float> velocity;
	vector3d<float> accelaration;
	vector3d<float> orientation;
	vector3d<float> angularVelocity;
	vector3d<float> angularAccelaration;
	vector3d<float> anchorPoint;

	Transform();
	virtual ~Transform();
}

#endif