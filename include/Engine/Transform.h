#ifndef TRANSFORMCOMPONENT
#define TRANSFORMCOMPONENT

#include "Irrlicht\irrlicht.h"
#include "Engine\Component.h"

class Transform : public Component {
public:
	irr::core::vector3df* position;
	irr::core::vector3df* rotation;
	irr::core::vector3df* velocity;

	Transform();
	virtual ~Transform();
};

#endif