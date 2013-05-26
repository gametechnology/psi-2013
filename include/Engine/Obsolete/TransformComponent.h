#ifndef PSI_TRANSFORM_COMPONENT
#define PSI_TRANSFORM_COMPONENT

#include "Engine\Component.h"

class TransformComponent : public Component {
public:
	irr::core::vector3df* position;
	irr::core::vector3df* rotation;
	irr::core::vector3df* velocity;
	irr::core::vector3df* acceleration;
	irr::core::vector3df* angularVelocity;
	irr::core::vector3df* angularAccelaration;
	irr::core::vector3df* radii;

	float mass;
	irr::core::vector3df force;

	TransformComponent();
	virtual void init();
	virtual void update();
	virtual ~TransformComponent();
};

#endif