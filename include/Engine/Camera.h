#ifndef CAMERA
#define CAMERA

#include "Entity.h"

using namespace irr;
using namespace core;

class Camera : public Entity {
public:
	Camera(Composite* parent, vector3df position = vector3df(0, 0, 0), vector3df lookAt = vector3df(0, 0, 100));
	virtual ~Camera();
	
	irr::scene::ICameraSceneNode* getCameraNode();
	void onAdd();

	void setTarget(irr::core::vector3df target);
	void setUpVector(irr::core::vector3df up);
private:
	irr::scene::ICameraSceneNode* node;
};


#endif