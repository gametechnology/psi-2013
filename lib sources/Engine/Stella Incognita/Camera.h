#include "Entity.h"

#ifndef CAMERA
#define CAMERA

using namespace irr;
using namespace core;

class Camera : public Entity
{
public:
	Camera(Composite* parent);
	virtual ~Camera();

	irr::scene::ICameraSceneNode* getCameraNode();
	void update();
private:
	bool parentIsEntity;
	vector3df oldParentPosition;
	vector3df oldParentOrientation;
};

#endif