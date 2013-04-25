#ifndef CAMERA
#define CAMERA

#include "Entity.h"

using namespace irr;
using namespace core;

class Camera : public Entity {
public:
	Camera();
	virtual ~Camera();
	
	irr::scene::ICameraSceneNode* getCameraNode();
	void onAdd();

	void setTarget(irr::core::vector3df target);
	void setUpVector(irr::core::vector3df up);
private:
	irr::scene::ICameraSceneNode* node;
};


#endif