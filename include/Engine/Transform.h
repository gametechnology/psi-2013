#ifndef TRANSFORMCOMPONENT
#define TRANSFORMCOMPONENT

#include "Irrlicht\irrlicht.h"
#include "Engine\Component.h"

class Transform : public Component {
public:
	irr::core::vector3df* position;
	irr::core::vector3df* rotation;
	irr::core::vector3df* velocity;
	irr::core::vector3df* acceleration;
	irr::core::vector3df* angularVelocity;
	irr::core::vector3df* angularAccelaration;

	float mass;
	irr::core::vector3df force;

	Transform();
	virtual void init();
	virtual void update();
	virtual ~Transform();
};

#endif